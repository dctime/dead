#include "DEAD_player.h"
#include <DEAD_controllable_player.h>
#include <DEAD_filepaths.h>
#include <DEAD_game.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <functional>
#include <iostream>
#include <items/DEAD_house_key.h>
#include <items/weapons/DEAD_bat.h>
#include <items/weapons/guns/DEAD_pistol.h>
#include <memory>
#include <zombies/DEAD_zombie.h>

const int DEAD_Game::BULLET_COLLISION_DELAY = 1000.0 / 60;
const int DEAD_Game::MAIN_LOOP_DELAY = 1000.0 / 60;

DEAD_Game::DEAD_Game(std::string playerName)
    : SCREEN_WIDTH(1080), SCREEN_HEIGHT(760),
      window(SDL_CreateWindow("DEAD", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, this->SCREEN_WIDTH,
                              this->SCREEN_HEIGHT, SDL_WINDOW_SHOWN)),
      map(std::make_unique<DEAD_Map>()),
      itemDropLayer(std::make_unique<DEAD_ItemDropLayer>()),
      decorationLayerBuilder(
          std::make_unique<DEAD_DecorationLayerBuilder>(this)),
      dataBaseConnector(std::make_unique<DEAD_DataBaseConnector>()),
      running(true), ticking(true), passTicks(0) {

  SDL_Log("Game Init");

  int genStatus =
      system(("./" + DEAD_FilePaths::DEAD_QUOTE_GEN + " &").c_str());
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
  }

  // load support for the JPG and PNG image formats
  int flags = IMG_INIT_PNG;
  int initted = IMG_Init(flags);
  if ((initted & flags) != flags) {
    printf("IMG_Init: Failed to init required png support!\n");
    printf("IMG_Init: %s\n", IMG_GetError());
    // handle error
  }

  if (TTF_Init() == -1) {
    SDL_Log("Font Crashed");
  }

  if (window == NULL) {
    SDL_Log("Unable to init window: %s", SDL_GetError());
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n",
           Mix_GetError());
  }

  this->soundDirector = std::make_unique<DEAD_SoundDirector>();
  this->map->loadMap();
  this->itemDropLayer->summonItemDrop<DEAD_Pistol>(7.5, 28.5);
  this->itemDropLayer->summonItemDrop<DEAD_Bat>(7.5, 27.5);
  this->itemDropLayer->summonItemDrop<DEAD_HouseKey>(7.5, 29.5);
  this->decorationLayerBuilder->build(this->decorationLayer);

  this->player = std::make_unique<DEAD_ControllablePlayer>(this, playerName);
  std::vector<DEAD_Map::MapLocation> locs = this->map->getPlayerPointLocs();
  if (locs.size() > 0) {
    // set the first player point
    this->player->setPos(locs[0].x, locs[0].y);
  }
  this->map->getMapSpawner()->initAccess(this);
  this->renderer = std::make_unique<DEAD_Renderer>(this->window, this, 50);
  this->renderer3D = std::make_unique<DEAD_Renderer3D>(
      this->window, this->renderer.get(), this);

  this->bulletDirector = std::make_unique<DEAD_BulletDirector>(this);
  this->collisionDirector = std::make_unique<DEAD_CollisionDirector>(this);
  this->zombieDirector = std::make_unique<DEAD_ZombieDirector>(this);

  this->bulletCollisionID =
      (SDL_AddTimer(DEAD_Game::BULLET_COLLISION_DELAY,
                    this->bulletCheckCollisionCallback, this));
  this->mainLoopID = SDL_AddTimer(DEAD_Game::MAIN_LOOP_DELAY,
                                  this->playerMovementCallback, this);
  this->zombieSpawnID = SDL_AddTimer(3000, this->spawnZombieCallback, this);
  this->lastTimeLoopTicks = SDL_GetTicks64();
}

DEAD_Game::~DEAD_Game() {
  SDL_RemoveTimer(this->bulletCollisionID);
  SDL_RemoveTimer(this->mainLoopID);
  SDL_DestroyWindow(this->window);
  IMG_Quit();
  SDL_Quit();
  SDL_Log("Game Destroyed");
}

void DEAD_Game::mapTick() { this->eventHandle(); }

void DEAD_Game::eventHandle() {
  SDL_Event event;
  SDL_PollEvent(&event);

  std::function<void(void *)> p;
  switch (event.type) {
  case SDL_USEREVENT:
    p = (void (*)(void *))event.user.data1;
    p((DEAD_Game *)event.user.data2);

    break;
  case SDL_QUIT:
    this->running = false;
    break;
  default:
    if (!ticking)
      break;
    this->player->playerEvents(event);
  }
}

void DEAD_Game::run() {
  while (this->running) {
    this->mapTick();
  }
}
DEAD_Map *DEAD_Game::getMap() { return this->map.get(); }

DEAD_Player *DEAD_Game::getPlayer() { return this->player.get(); }

DEAD_Renderer *DEAD_Game::getRenderer() { return this->renderer.get(); }

DEAD_BulletDirector *DEAD_Game::getBulletDirector() {
  return this->bulletDirector.get();
}

DEAD_CollisionDirector *DEAD_Game::getCollisionDirector() {
  return this->collisionDirector.get();
}

DEAD_ItemDropLayer *DEAD_Game::getItemDropLayer() {
  return this->itemDropLayer.get();
}

DEAD_DecorationLayer *DEAD_Game::getDecorationLayer() {
  return this->decorationLayer.get();
}

DEAD_ZombieDirector *DEAD_Game::getZombieDirector() {
  return this->zombieDirector.get();
}

DEAD_SoundDirector *DEAD_Game::getSoundDirector() {
  return this->soundDirector.get();
}

DEAD_DataBaseConnector *DEAD_Game::getDataBaseConnector() {
  return this->dataBaseConnector.get();
}

int DEAD_Game::getPassTicks() { return this->passTicks; }

void DEAD_Game::checkPlayerDied() {
  if (this->getPlayer()->getHealth() > 0)
    return;
  std::cout << "YOU DIED!" << std::endl;
  std::cout << "You Survived " << this->passTicks / 1000 << " seconds"
            << std::endl;
  this->renderer->startYouDied();
  this->soundDirector->playYouDiedSound();
  this->dataBaseConnector->sendDataToDataBase(this->player->getEntityName(),
                                              this->getPassTicks() / 1000);
  ticking = false;
}

Uint32 DEAD_Game::bulletCheckCollisionCallback(Uint32 interval, void *param) {
  SDL_Event event;
  SDL_UserEvent userEvent;

  userEvent.type = SDL_USEREVENT;
  userEvent.code = 0;
  userEvent.data1 = (void *)&DEAD_Game::checkAndDeleteCollisionBullets;
  userEvent.data2 = param;

  event.type = SDL_USEREVENT;
  event.user = userEvent;

  SDL_PushEvent(&event);
  return interval;
}

Uint32 DEAD_Game::playerMovementCallback(Uint32 interval, void *param) {
  SDL_Event event;
  SDL_UserEvent userEvent;

  userEvent.type = SDL_USEREVENT;
  userEvent.code = 0;
  userEvent.data1 = (void *)&DEAD_Game::mainLoop;
  userEvent.data2 = param;

  event.type = SDL_USEREVENT;
  event.user = userEvent;

  SDL_PushEvent(&event);
  return interval;
}

Uint32 DEAD_Game::spawnZombieCallback(Uint32 interval, void *param) {
  SDL_Event event;
  SDL_UserEvent userEvent;

  userEvent.type = SDL_USEREVENT;
  userEvent.code = 0;
  userEvent.data1 = (void *)&DEAD_Game::zombieSpawn;
  userEvent.data2 = param;

  event.type = SDL_USEREVENT;
  event.user = userEvent;

  SDL_PushEvent(&event);
  return interval;
}

int DEAD_Game::getSecretNumber() { return 7; }

void DEAD_Game::mainLoop(DEAD_Game *game) {
  if (game->ticking) {
    game->passTicks += SDL_GetTicks64() - game->lastTimeLoopTicks;
    game->lastTimeLoopTicks = SDL_GetTicks64();
    game->player->handleKeyState();
    game->player->handlePlayerRotation();
    game->bulletDirector->tickBullets();
    game->getZombieDirector()->tickZombies();
    game->checkPlayerDied();
  }
  
  // game->renderer->render2D();
  game->renderer3D->render();
}

void DEAD_Game::checkAndDeleteCollisionBullets(DEAD_Game *game) {
  if (!game->ticking)
    return;
  game->bulletDirector->checkAndDeleteCollisionBullets();
}

void DEAD_Game::zombieSpawn(DEAD_Game *game) {
  if (!game->ticking)
    return;
  // game->getMap()->getMapSpawner()->randomSpawnAZombie();
}
