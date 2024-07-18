#include "DEAD_player.h"
#include <DEAD_game.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <map>
#include <memory>

DEAD_Game::DEAD_Game(DEAD_ControllablePlayer *player)
    : SCREEN_WIDTH(720), SCREEN_HEIGHT(480),
      window(SDL_CreateWindow("DEAD", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, this->SCREEN_WIDTH,
                              this->SCREEN_HEIGHT, SDL_WINDOW_SHOWN)),
      map(new DEAD_Map()), renderer(new DEAD_Renderer(this->window, this)),
      player(player), bulletDirector(new DEAD_BulletDirector(this)),
      collisionDirector(new DEAD_CollisionDirector(this)),
      itemDropLayer(std::make_shared<DEAD_ItemDropLayer>()){


  SDL_Log("Game Init");
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
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

  std::vector<DEAD_Map::MapLocation> locs = this->map->getPlayerPointLocs();
  if (locs.size() > 0) {
    // set the first player point
  this->player->setPos(locs[0].x, locs[0].y);
  }

  this->player->setGame(this);
}

DEAD_Game::~DEAD_Game() {
  SDL_DestroyWindow(this->window);
  IMG_Quit();
  SDL_Quit();
  SDL_Log("Game Destroyed");
  delete this->renderer;
  delete this->map;
  delete this->bulletDirector;
  delete this->collisionDirector;
}

void DEAD_Game::tick() {
  this->player->handlePlayerRotation();
  this->eventHandle();
  this->player->handleKeyState();
  this->bulletDirector->tickBullets();
  this->renderer->moveRenderAnchor(this->player->getPos().x,
                                   this->player->getPos().y);
  this->renderer->render();
}

void DEAD_Game::eventHandle() {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
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

DEAD_Map *DEAD_Game::getMap() { return this->map; }

DEAD_Player *DEAD_Game::getPlayer() { return this->player; }

DEAD_Renderer *DEAD_Game::getRenderer() { return this->renderer; }

DEAD_BulletDirector *DEAD_Game::getBulletDirector() {
  return this->bulletDirector;
}

DEAD_CollisionDirector *DEAD_Game::getCollisionDirector() {
  return this->collisionDirector;
}

std::shared_ptr<DEAD_ItemDropLayer> DEAD_Game::getItemDropLayer() {
  return this->itemDropLayer;
}

