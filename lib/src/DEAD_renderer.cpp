#include "DEAD_item_drop.h"
#include "DEAD_zombie_director.h"
#include "map_objects/DEAD_map_object_base.h"
#include "zombies/DEAD_zombie.h"
#include <DEAD_filepaths.h>
#include <DEAD_game.h>
#include <DEAD_map.h>
#include <DEAD_player.h>
#include <DEAD_renderer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>

void DEAD_Renderer::getTextureFromSurface(SDL_Texture *&texture,
                                          std::string filePath) {
  SDL_Surface *textureSurface = IMG_Load(filePath.c_str());
  texture = SDL_CreateTextureFromSurface(this->renderer, textureSurface);
  SDL_FreeSurface(textureSurface);
}

DEAD_Renderer::DEAD_Renderer(SDL_Window *window, std::shared_ptr<DEAD_Game> game)
    : renderBlockSize(25), renderAnchor({.x = 0, .y = 0}) {

  if (window == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "[Renderer] Window is null");
  }

  this->renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
  if (this->renderer == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_RENDER, "[Renderer] %s", SDL_GetError());
  }

  getTextureFromSurface(this->itemTexture, DEAD_FilePaths::ITEM_TEXTURE_PNG);
  getTextureFromSurface(this->mapObjectTexture,
                        DEAD_FilePaths::MAP_OBJECT_PNG_FILE_PATH);
  getTextureFromSurface(this->playerTexture,
                        DEAD_FilePaths::PLAYER_TEXTURE_PNG);
  getTextureFromSurface(this->bulletTexture,
                        DEAD_FilePaths::BULLET_TEXTURE_PNG);
  getTextureFromSurface(this->zombiesTexture,
                        DEAD_FilePaths::ZOMBIES_TEXTURE_PNG);
  this->game = game;
}

DEAD_Renderer::~DEAD_Renderer() { 
  SDL_DestroyTexture(this->zombiesTexture);
  SDL_DestroyTexture(this->bulletTexture);
  SDL_DestroyTexture(this->itemTexture);
  SDL_DestroyTexture(this->playerTexture);
  SDL_DestroyTexture(this->mapObjectTexture);
  SDL_DestroyRenderer(this->renderer); 
}

void DEAD_Renderer::render() {
  SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
  SDL_RenderClear(this->renderer);

  this->renderMapObjects();
  this->renderItemDropLayer();
  this->renderBullets();
  this->renderPlayer(this->game->getPlayer());
  this->renderZombies(this->game->getZombieDirector());
  // this->drawZombieMovementMap();

  SDL_RenderPresent(this->renderer);
}

void DEAD_Renderer::renderMapObjects() {
  std::shared_ptr<DEAD_Map> map = this->game->getMap();

  float windowWidthMid = this->game->SCREEN_WIDTH / 2.0;
  float windowHeightMid = this->game->SCREEN_HEIGHT / 2.0;

  std::vector<std::vector<std::shared_ptr<DEAD_MapObjectBase>>> mapObjects =
      map->getMapObjects();

  for (int i = 0; i < mapObjects.size(); ++i) {
    this->renderRect.y =
        (i - this->renderAnchor.y) * this->renderBlockSize + windowHeightMid;
    for (int j = 0; j < mapObjects[i].size(); ++j) {
      this->renderRect.x =
          (j - this->renderAnchor.x) * this->renderBlockSize + windowWidthMid;

      const SDL_Rect *locationRect;
      bool isAir = false;

      SDL_Rect objectTextureRect = mapObjects[i][j]->getTextureRect();
      if (objectTextureRect.w == 0 && objectTextureRect.h == 0)
        isAir = true;

      if (!isAir) {

        SDL_RenderCopy(this->renderer, this->mapObjectTexture,
                       &objectTextureRect, &renderRect);
      }
    }
  }
}

void DEAD_Renderer::renderPlayer(std::shared_ptr<DEAD_Player> player) {
  this->renderEntity(player, this->playerTexture);
}

void DEAD_Renderer::renderEntity(std::shared_ptr<DEAD_Entity> entity, SDL_Texture* texture) {
  DEAD_Map::MapLocation pos = entity->getPos();
  SDL_Rect rect = entity->getTextureRect();

  int renderRectX = this->getEntityRenderLocation(entity, false).x;
  int renderRectY = this->getEntityRenderLocation(entity, false).y;
  SDL_Rect renderRect = {.x = renderRectX,
                         .y = renderRectY,
                         .w = (int)(entity->getSize() * this->renderBlockSize),
                         .h = (int)(entity->getSize() * this->renderBlockSize)};
  SDL_RenderCopyEx(this->renderer, texture, &rect, &renderRect,
                   entity->getRotation(), NULL, SDL_FLIP_NONE);
}

void DEAD_Renderer::renderZombies(const std::shared_ptr<DEAD_ZombieDirector>& zombieDirector) {
  for (std::shared_ptr<DEAD_Zombie> zombie : zombieDirector->getZombies()) {
    renderEntity(zombie, this->zombiesTexture);
  } 
}

ScreenLocation DEAD_Renderer::getEntityRenderLocation(std::shared_ptr<DEAD_Entity> entity,
                                                      bool mid) {
  ScreenLocation loc;
  loc.x = (entity->getPos().x - renderAnchor.x) * this->renderBlockSize -
          (entity->getSize() * this->renderBlockSize) / 2.0 +
          this->game->SCREEN_WIDTH / 2.0;
  loc.y = (entity->getPos().y - renderAnchor.y) * this->renderBlockSize -
          (entity->getSize() * this->renderBlockSize) / 2.0 +
          this->game->SCREEN_HEIGHT / 2.0;

  if (mid) {
    loc.x = loc.x + (entity->getSize() * this->renderBlockSize) / 2.0;
    loc.y = loc.y + (entity->getSize() * this->renderBlockSize) / 2.0;
  }
  return loc;
}


void DEAD_Renderer::renderBullets() {
  std::shared_ptr<DEAD_BulletDirector> director = this->game->getBulletDirector();
  std::set<std::shared_ptr<DEAD_Bullet>> bullets = director->getBullets();

  for (std::shared_ptr<DEAD_Bullet> bullet : bullets) {
    SDL_Rect textureRect = bullet->getBulletTextureRect();
    SDL_Rect renderRect = {
        .x = this->getBulletRenderLocation(bullet).x,
        .y = this->getBulletRenderLocation(bullet).y,
        .w = (int)(bullet->getBulletSize() * this->renderBlockSize),
        .h = (int)(bullet->getBulletSize() * this->renderBlockSize)};
    SDL_RenderCopy(this->renderer, this->bulletTexture, &textureRect,
                   &renderRect);
  }
}

ScreenLocation DEAD_Renderer::getBulletRenderLocation(std::shared_ptr<DEAD_Bullet> bullet) {
  ScreenLocation loc;
  loc.x =
      (bullet->getMapLocation().x - renderAnchor.x) * this->renderBlockSize -
      bullet->getBulletSize() * this->renderBlockSize / 2.0 +
      this->game->SCREEN_WIDTH / 2.0;
  loc.y =
      (bullet->getMapLocation().y - renderAnchor.y) * this->renderBlockSize -
      bullet->getBulletSize() * this->renderBlockSize / 2.0 +
      this->game->SCREEN_HEIGHT / 2.0;

  return loc;
}

void DEAD_Renderer::renderItemDropLayer() {
  std::shared_ptr<DEAD_ItemDropLayer> itemDropLayer = this->game->getItemDropLayer();
  std::set<std::shared_ptr<DEAD_ItemDrop>> itemDrops =
      itemDropLayer->getItemDrops();

  for (std::shared_ptr<DEAD_ItemDrop> itemDrop : itemDrops) {
    SDL_Rect textureRect = itemDrop->getItem()->getItemTextureRect();
    SDL_Rect renderRect = {
        .x = this->getItemDropRenderLocation(itemDrop).x,
        .y = this->getItemDropRenderLocation(itemDrop).y,
        .w = (int)(itemDrop->getSize() * this->renderBlockSize),
        .h = (int)(itemDrop->getSize() * this->renderBlockSize)};
    SDL_RenderCopy(this->renderer, this->itemTexture, &textureRect,
                   &renderRect);
  }
}

ScreenLocation DEAD_Renderer::getItemDropRenderLocation(
    std::shared_ptr<DEAD_ItemDrop> itemDrop) {
  ScreenLocation loc;
  loc.x = (itemDrop->getLoc().x - renderAnchor.x) * this->renderBlockSize -
          itemDrop->getSize() * this->renderBlockSize / 2.0 +
          this->game->SCREEN_WIDTH / 2.0;
  loc.y = (itemDrop->getLoc().y - renderAnchor.y) * this->renderBlockSize -
          itemDrop->getSize() * this->renderBlockSize / 2.0 +
          this->game->SCREEN_HEIGHT / 2.0;

  return loc;
}

void DEAD_Renderer::drawZombieMovementMap() {
  std::shared_ptr<DEAD_ZombieDirector> zombieDirector = this->game->getZombieDirector();
  for (int y = 0; y < this->game->getMap()->getMapSize().height; y++) {
    for (int x = 0; x < this->game->getMap()->getMapSize().width; x++) {
      DEAD_ZombieDirector::ZombieVector drawingVector = zombieDirector->getLocMovementMapData(x, y).vector;
      ScreenLocation startLoc = this->getPointRenderLocation(x+0.5, y+0.5);
      ScreenLocation endLoc = this->getPointRenderLocation(x+0.5+drawingVector.vectorX, y+0.5+drawingVector.vectorY);
      SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 0);
      SDL_RenderDrawLine(this->renderer, startLoc.x, startLoc.y, endLoc.x, endLoc.y);
    }
  }
  
  for (std::shared_ptr<DEAD_Zombie> zombie : this->game->getZombieDirector()->getZombies()) {
    ScreenLocation zombieLoc = this->getPointRenderLocation(zombie->getPos().x, zombie->getPos().y);
    DEAD_ZombieDirector::ZombieVector zombieMoveVec = zombieDirector->getMovementVector(zombie->getPos().x, zombie->getPos().y);
    ScreenLocation zombieMoveEndScreen = this->getPointRenderLocation(zombieMoveVec.vectorX+zombie->getPos().x, zombieMoveVec.vectorY+zombie->getPos().y);
    SDL_RenderDrawLine(this->renderer, zombieLoc.x, zombieLoc.y, zombieMoveEndScreen.x, zombieMoveEndScreen.y);
  }
}

ScreenLocation DEAD_Renderer::getPointRenderLocation(double x, double y) {
  ScreenLocation loc;
  loc.x = (x - renderAnchor.x) * this->renderBlockSize +
          this->game->SCREEN_WIDTH / 2.0;
  loc.y = (y - renderAnchor.y) * this->renderBlockSize +
          this->game->SCREEN_HEIGHT / 2.0;

  return loc;
}

void DEAD_Renderer::moveRenderAnchor(double x, double y) {
  RenderAnchor anchor = {.x = x, .y = y};
  this->renderAnchor = anchor;
}
