#include <DEAD_filepaths.h>
#include <DEAD_game.h>
#include <DEAD_map.h>
#include <DEAD_renderer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>
#include <vector>

const SDL_Rect DEAD_LocationRectMapObject::WOOD_LOCATION_RECT = {
    .x = 100, .y = 0, .w = 100, .h = 100};
const SDL_Rect DEAD_LocationRectMapObject::STONE_LOCATION_RECT = {
    .x = 0, .y = 0, .w = 100, .h = 100};


DEAD_Renderer::DEAD_Renderer() {}

DEAD_Renderer::DEAD_Renderer(SDL_Window *window, DEAD_Game *game) {
  if (window == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "[Renderer] Window is null");
  }
  this->renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

  if (this->renderer == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_RENDER, "[Renderer] %s", SDL_GetError());
  }
  this->renderer = SDL_GetRenderer(window);
  
  SDL_Surface *mapObjectSurface = IMG_Load(DEAD_FilePaths::MAP_OBJECT_PNG_FILE_PATH.c_str());
  if (mapObjectSurface == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
                 "[Renderer] Cant Find map_objects.png");
  }
  this->mapObjectTexture =
      SDL_CreateTextureFromSurface(this->renderer, mapObjectSurface);
  SDL_FreeSurface(mapObjectSurface);

  SDL_Surface* playerTextureSurface = IMG_Load(DEAD_FilePaths::PLAYER_TEXTURE_PNG.c_str());
  this->playerTexture = SDL_CreateTextureFromSurface(this->game->getRenderer(), playerTextureSurface);
  SDL_FreeSurface(playerTextureSurface);

  this->game = game;
}

DEAD_Renderer::~DEAD_Renderer() { SDL_DestroyRenderer(this->renderer); }

void DEAD_Renderer::render() {
  this->renderAnchor.x = 1.5;
  this->renderAnchor.y = 2;
  this->renderMapObjects();
}

void DEAD_Renderer::renderMapObjects() {
  DEAD_Map *map = this->game->getMap();
  SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
  SDL_RenderClear(this->renderer);

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
        locationRect = &DEAD_LocationRectMapObject::STONE_LOCATION_RECT;
        break;
      case 'w':
        locationRect = &DEAD_LocationRectMapObject::WOOD_LOCATION_RECT;
        break;
      default:
        isAir = true;
      }
      if (!isAir)
        SDL_RenderCopy(this->renderer, this->mapObjectTexture, locationRect, &renderRect);

    }
  }
  SDL_RenderPresent(this->renderer);
}
