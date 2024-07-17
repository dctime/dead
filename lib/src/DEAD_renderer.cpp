#include "map_objects/DEAD_map_object_base.h"
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
#include <vector>

DEAD_Renderer::DEAD_Renderer(SDL_Window *window, DEAD_Game *game)
    : renderBlockSize(50), renderAnchor({.x = 0, .y = 0}) {

  if (window == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "[Renderer] Window is null");
  }
  this->renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

  if (this->renderer == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_RENDER, "[Renderer] %s", SDL_GetError());
  }

  SDL_Surface *mapObjectSurface =
      IMG_Load(DEAD_FilePaths::MAP_OBJECT_PNG_FILE_PATH.c_str());
  if (mapObjectSurface == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
                 "[Renderer] Cant Find map_objects.png");
  }
  this->mapObjectTexture =
      SDL_CreateTextureFromSurface(this->renderer, mapObjectSurface);
  SDL_FreeSurface(mapObjectSurface);

  SDL_Surface *playerTextureSurface =
      IMG_Load(DEAD_FilePaths::PLAYER_TEXTURE_PNG.c_str());
  this->playerTexture =
      SDL_CreateTextureFromSurface(this->renderer, playerTextureSurface);
  SDL_FreeSurface(playerTextureSurface);

  SDL_Surface *bulletTextureSurface =
      IMG_Load(DEAD_FilePaths::BULLET_TEXTURE_PNG.c_str());
  this->bulletTexture =
      SDL_CreateTextureFromSurface(this->renderer, bulletTextureSurface);
  SDL_FreeSurface(bulletTextureSurface);

  this->game = game;
}

DEAD_Renderer::~DEAD_Renderer() { SDL_DestroyRenderer(this->renderer); }

void DEAD_Renderer::render() {
  SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
  SDL_RenderClear(this->renderer);

  this->renderMapObjects();
  this->renderBullets();
  this->renderPlayer(this->game->getPlayer());

  SDL_RenderPresent(this->renderer);
}

void DEAD_Renderer::renderMapObjects() {
  DEAD_Map *map = this->game->getMap();

  float windowWidthMid = this->game->SCREEN_WIDTH / 2.0;
  float windowHeightMid = this->game->SCREEN_HEIGHT / 2.0;

  std::vector<std::vector<DEAD_MapObjectBase *>> mapObjects =
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

void DEAD_Renderer::renderPlayer(DEAD_Player *player) {
  DEAD_Map::MapLocation pos = player->getPos();
  SDL_Rect rect = player->getPlayerTextureRect();

  int renderRectX = this->getPlayerRenderLocation(player, false).x;
  int renderRectY = this->getPlayerRenderLocation(player, false).y;
  SDL_Rect renderRect = {.x = renderRectX,
                         .y = renderRectY,
                         .w = (int)(player->getSize() * this->renderBlockSize),
                         .h = (int)(player->getSize() * this->renderBlockSize)};
  SDL_RenderCopyEx(this->renderer, this->playerTexture, &rect, &renderRect,
                   player->getRotation(), NULL, SDL_FLIP_NONE);
}

ScreenLocation DEAD_Renderer::getPlayerRenderLocation(DEAD_Player *player,
                                                      bool mid) {
  ScreenLocation loc;
  loc.x = (player->getPos().x - renderAnchor.x) * this->renderBlockSize -
          (player->getSize() * this->renderBlockSize) / 2.0 +
          this->game->SCREEN_WIDTH / 2.0;
  loc.y = (player->getPos().y - renderAnchor.y) * this->renderBlockSize -
          (player->getSize() * this->renderBlockSize) / 2.0 +
          this->game->SCREEN_HEIGHT / 2.0;

  if (mid) {
    loc.x = loc.x + (player->getSize() * this->renderBlockSize) / 2.0;
    loc.y = loc.y + (player->getSize() * this->renderBlockSize) / 2.0;
  }
  return loc;
}

void DEAD_Renderer::renderBullets() {
  DEAD_BulletDirector *director = this->game->getBulletDirector();
  std::set<DEAD_Bullet *> bullets = director->getBullets();

  for (DEAD_Bullet *bullet : bullets) {
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

ScreenLocation DEAD_Renderer::getBulletRenderLocation(DEAD_Bullet *bullet) {
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

void DEAD_Renderer::moveRenderAnchor(double x, double y) {
  RenderAnchor anchor = {.x = x, .y = y};
  this->renderAnchor = anchor;
}
