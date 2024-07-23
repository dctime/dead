#include "DEAD_player.h"
#include <DEAD_game.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <functional>
#include <iostream>
#include <memory>
#include <DEAD_controllable_player.h>
#include <zombies/DEAD_zombie.h>

const int DEAD_Game::BULLET_COLLISION_DELAY = 1000.0 / 60;
const int DEAD_Game::MAIN_LOOP_DELAY = 1000.0 / 60;

DEAD_Game::DEAD_Game()
    : SCREEN_WIDTH(720), SCREEN_HEIGHT(480),
      window(SDL_CreateWindow("DEAD", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, this->SCREEN_WIDTH,
                              this->SCREEN_HEIGHT, SDL_WINDOW_SHOWN)),
      map(std::make_shared<DEAD_Map>()), 
      itemDropLayer(std::make_shared<DEAD_ItemDropLayer>()) {

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

  if (window == NULL) {
    SDL_Log("Unable to init window: %s", SDL_GetError());
  }

  this->map->loadMap();

  

}

void DEAD_Game::initObjectThatHasSharedFromThis() {
  this->map->getMapSpawner()->initAccess(shared_from_this()); 
  this->renderer =
      std::make_shared<DEAD_Renderer>(this->window, shared_from_this());
  this->bulletDirector =
      std::make_shared<DEAD_BulletDirector>(shared_from_this());
  this->collisionDirector =
      std::make_shared<DEAD_CollisionDirector>(shared_from_this());
  this->zombieDirector = std::make_shared<DEAD_ZombieDirector>(shared_from_this(), this->getMap()->getMapSize().width, this->getMap()->getMapSize().height);
  // std::shared_ptr<DEAD_Zombie> zombie = std::make_shared<DEAD_Zombie>(shared_from_this());
  // zombie->setPos(1.5, 1.5);
  // this->zombieDirector->registerZombie(zombie);
  

  this->bulletCollisionID = (SDL_AddTimer(
    DEAD_Game::BULLET_COLLISION_DELAY, this->bulletCheckCollisionCallback, shared_from_this().get()));
  this->mainLoopID = SDL_AddTimer(DEAD_Game::MAIN_LOOP_DELAY, this->playerMovementCallback, shared_from_this().get()); 
  this->zombieSpawnID = SDL_AddTimer(1000, this->spawnZombieCallback, shared_from_this().get());
  
}

DEAD_Game::~DEAD_Game() {
  SDL_RemoveTimer(this->bulletCollisionID);
  SDL_RemoveTimer(this->mainLoopID);
  SDL_DestroyWindow(this->window);
  IMG_Quit();
  SDL_Quit();
  SDL_Log("Game Destroyed");
}

void DEAD_Game::tick() {
  
  this->eventHandle();
  this->renderer->moveRenderAnchor(this->player->getPos().x,
                                   this->player->getPos().y);
  this->renderer->render();
}

void DEAD_Game::eventHandle() {
  SDL_Event event;
  SDL_PollEvent(&event);

  
  std::function<void(void*)> p; 
  switch (event.type) {
  case SDL_USEREVENT: 
    p = (void(*)(void*))event.user.data1;
    p((DEAD_Game*)event.user.data2);
    break;
  case SDL_QUIT:
    this->running = false;
    break;
  default:
    this->player->playerEvents(event);
  }
}

void DEAD_Game::run() {
  while (this->running) {
    this->tick();
  }
}

std::shared_ptr<DEAD_Map> DEAD_Game::getMap() { return this->map; }

std::shared_ptr<DEAD_Player> DEAD_Game::getPlayer() { return this->player; }
void DEAD_Game::setPlayer(std::shared_ptr<DEAD_ControllablePlayer> player) {
  this->player = player;
  std::vector<DEAD_Map::MapLocation> locs = this->map->getPlayerPointLocs();
  if (locs.size() > 0) {
    // set the first player point
    this->player->setPos(locs[0].x, locs[0].y);
  }
}

std::shared_ptr<DEAD_Renderer> DEAD_Game::getRenderer() {
  return this->renderer;
}

std::shared_ptr<DEAD_BulletDirector> DEAD_Game::getBulletDirector() {
  return this->bulletDirector;
}

std::shared_ptr<DEAD_CollisionDirector> DEAD_Game::getCollisionDirector() {
  return this->collisionDirector;
}

std::shared_ptr<DEAD_ItemDropLayer> DEAD_Game::getItemDropLayer() {
  return this->itemDropLayer;
}

std::shared_ptr<DEAD_ZombieDirector> DEAD_Game::getZombieDirector() {
  return this->zombieDirector;
}

void DEAD_Game::checkPlayerDied() {
  if (this->getPlayer()->getHealth() > 0) return;
  std::cout << "YOU DIED!" << std::endl;
}

Uint32 DEAD_Game::bulletCheckCollisionCallback(Uint32 interval, void *param) {
  SDL_Event event;
  SDL_UserEvent userEvent;

  userEvent.type = SDL_USEREVENT;
  userEvent.code = 0;
  userEvent.data1 = (void*)&DEAD_Game::checkAndDeleteCollisionBullets;
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
  userEvent.data1 = (void*)&DEAD_Game::mainLoop;
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
  userEvent.data1 = (void*)&DEAD_Game::zombieSpawn;
  userEvent.data2 = param;

  event.type = SDL_USEREVENT;
  event.user = userEvent;

  SDL_PushEvent(&event);
  return interval;
}

int DEAD_Game::getSecretNumber() { return 7; }

void DEAD_Game::mainLoop(DEAD_Game* game) {
  game->player->handleKeyState();
  // game->getZombieDirector()->updateHeatMapValue();
  game->player->handlePlayerRotation();
  game->bulletDirector->tickBullets();
  game->getZombieDirector()->tickZombies();
  game->checkPlayerDied();
}
void DEAD_Game::checkAndDeleteCollisionBullets(DEAD_Game* game) {
  game->bulletDirector->checkAndDeleteCollisionBullets();
}

void DEAD_Game::zombieSpawn(DEAD_Game* game) {
  game->getMap()->getMapSpawner()->randomSpawnAZombie();
}
