#include <DEAD_filepaths.h>
#include <DEAD_game.h>
#include <DEAD_map.h>
#include <DEAD_renderer.h>
#include <DEAD_player.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <vector>

const SDL_Rect DEAD_RectLocMapObjects::STONE = {
    .x = 0, .y = 0, .w = 100, .h = 100};
const SDL_Rect DEAD_RectLocMapObjects::WOOD = {
    .x = 100, .y = 0, .w = 100, .h = 100};

DEAD_Renderer::DEAD_Renderer() {}

DEAD_Renderer::DEAD_Renderer(SDL_Window *window, DEAD_Game *game)
: entitySize(50) {


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


  this->game = game;
}

DEAD_Renderer::~DEAD_Renderer() { SDL_DestroyRenderer(this->renderer); }

void DEAD_Renderer::render() {
  this->renderAnchor.x = 0;
  this->renderAnchor.y = 0;


  SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
  SDL_RenderClear(this->renderer);

  this->renderMapObjects();
  this->renderPlayer(this->game->getPlayer());

  SDL_RenderPresent(this->renderer);
}

void DEAD_Renderer::renderMapObjects() {
  DEAD_Map *map = this->game->getMap();
  
  float windowWidthMid = this->game->SCREEN_WIDTH / 2.0;
  float windowHeightMid = this->game->SCREEN_HEIGHT / 2.0;

  std::vector<std::vector<char>> mapObjects = map->getMapObjects();

  for (int i = 0; i < mapObjects.size(); ++i) {
    this->renderRect.y =
        (i - this->renderAnchor.y) * this->renderBlockSize + windowHeightMid;
    for (int j = 0; j < mapObjects[i].size(); ++j) {
      this->renderRect.x =
          (j - this->renderAnchor.x) * this->renderBlockSize + windowWidthMid;

      const SDL_Rect *locationRect;
      bool isAir = false;
      switch (mapObjects[i][j]) {
      case 's':
        locationRect = &DEAD_RectLocMapObjects::STONE;
        break;
      case 'w':
        locationRect = &DEAD_RectLocMapObjects::WOOD;
        break;
      default:
        isAir = true;
      }
      if (!isAir)
        SDL_RenderCopy(this->renderer, this->mapObjectTexture, locationRect,
  &renderRect);

    }
  }
}

void DEAD_Renderer::renderPlayer(DEAD_Player* player) {
  DEAD_Player::Position* pos = player->getPos();
  SDL_Rect rect = player->getPlayerTextureRect();


  int renderRectX = this->getPlayerRenderLocation(player, false).x;
  int renderRectY = this->getPlayerRenderLocation(player, false).y;
  SDL_Rect renderRect = {.x=renderRectX, .y=renderRectY, .w=this->entitySize, .h=entitySize};
  SDL_RenderCopyEx(this->renderer, this->playerTexture, &rect, &renderRect, player->getRotation(), NULL, SDL_FLIP_NONE);
}

ScreenLocation DEAD_Renderer::getPlayerRenderLocation(DEAD_Player* player, bool mid) {
  ScreenLocation loc;
  loc.x = (player->getPos()->x - renderAnchor.x) * this->renderBlockSize - this->entitySize / 2.0 + this->game->SCREEN_WIDTH / 2.0;
  loc.y = (player->getPos()->y - renderAnchor.y) * this->renderBlockSize - this->entitySize / 2.0 + this->game->SCREEN_HEIGHT / 2.0;

  if (mid) {
    loc.x = loc.x + this->entitySize / 2.0;
    loc.y = loc.y + this->entitySize / 2.0;
  }
  return loc;
}









