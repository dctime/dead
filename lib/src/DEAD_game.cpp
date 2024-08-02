#include "DEAD_player.h"
#include <DEAD_controllable_player.h>
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
#include <guns/DEAD_pistol.h>
#include <iostream>
#include <items/DEAD_house_key.h>
#include <memory>
#include <weapons/DEAD_bat.h>
#include <zombies/DEAD_zombie.h>

const int DEAD_Game::BULLET_COLLISION_DELAY = 1000.0 / 60;
const int DEAD_Game::MAIN_LOOP_DELAY = 1000.0 / 60;

DEAD_Game::DEAD_Game()
    : SCREEN_WIDTH(1080), SCREEN_HEIGHT(760),
      window(SDL_CreateWindow("DEAD", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, this->SCREEN_WIDTH,
                              this->SCREEN_HEIGHT, SDL_WINDOW_SHOWN)),
      map(std::make_unique<DEAD_Map>()),
      itemDropLayer(std::make_unique<DEAD_ItemDropLayer>()), running(true),
      ticking(true) {

  SDL_Log("Game Init");
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
  this->player = std::make_unique<DEAD_ControllablePlayer>(this);
  std::vector<DEAD_Map::MapLocation> locs = this->map->getPlayerPointLocs();
  if (locs.size() > 0) {
    // set the first player point
    this->player->setPos(locs[0].x, locs[0].y);
  }
  this->map->getMapSpawner()->initAccess(this);
  this->renderer = std::make_unique<DEAD_Renderer>(this->window, this);
  this->bulletDirector = std::make_unique<DEAD_BulletDirector>(this);
  this->collisionDirector = std::make_unique<DEAD_CollisionDirector>(this);
  this->zombieDirector = std::make_unique<DEAD_ZombieDirector>(this);

  this->bulletCollisionID =
      (SDL_AddTimer(DEAD_Game::BULLET_COLLISION_DELAY,
                    this->bulletCheckCollisionCallback, this));
  this->mainLoopID = SDL_AddTimer(DEAD_Game::MAIN_LOOP_DELAY,
                                  this->playerMovementCallback, this);
  this->zombieSpawnID = SDL_AddTimer(500, this->spawnZombieCallback, this);
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

DEAD_ZombieDirector *DEAD_Game::getZombieDirector() {
  return this->zombieDirector.get();
}

DEAD_SoundDirector *DEAD_Game::getSoundDirector() {
  return this->soundDirector.get();
}

void DEAD_Game::checkPlayerDied() {
  if (this->getPlayer()->getHealth() > 0)
    return;
  std::cout << "YOU DIED!" << std::endl;
  this->renderer->startYouDied();
  this->soundDirector->playYouDiedSound();
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
    game->player->handleKeyState();
    game->player->handlePlayerRotation();
    game->bulletDirector->tickBullets();
    game->getZombieDirector()->tickZombies();
    game->checkPlayerDied();
    game->renderer->moveRenderAnchor(game->player->getPos().x,
                                     game->player->getPos().y);
  }
  game->renderer->render();
}
void DEAD_Game::checkAndDeleteCollisionBullets(DEAD_Game *game) {
  if (!game->ticking) return;
  game->bulletDirector->checkAndDeleteCollisionBullets();
}

void DEAD_Game::zombieSpawn(DEAD_Game *game) {
  if (!game->ticking) return;
  game->getMap()->getMapSpawner()->randomSpawnAZombie();
}
