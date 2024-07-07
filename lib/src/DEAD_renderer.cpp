#include <DEAD_renderer.h>
#include <DEAD_filepaths.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>

const SDL_Rect DEAD_Renderer::WOOD_LOCATION_RECT = {.x=100, .y=0, .w=100, .h=100};
const SDL_Rect DEAD_Renderer::STONE_LOCATION_RECT = {.x=0, .y=0, .w=100, .h=100};

DEAD_Renderer::DEAD_Renderer() {}

DEAD_Renderer::DEAD_Renderer(SDL_Window* window) {
  if (window == NULL) { SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "[Renderer] Window is null"); }
  this->renderer =
      SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

  if (this->renderer == NULL) { SDL_LogError(SDL_LOG_CATEGORY_RENDER, "[Renderer] %s", SDL_GetError()); }
  this->renderer = SDL_GetRenderer(window);
  SDL_Surface *mapObjectSurface = IMG_Load("assets/imgs/map_objects.png");
  if (mapObjectSurface == NULL) { SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "[Renderer] Cant Find map_objects.png"); }
  this->mapObjectTexture = SDL_CreateTextureFromSurface(this->renderer, mapObjectSurface);
  SDL_FreeSurface(mapObjectSurface);
}

DEAD_Renderer::~DEAD_Renderer() {
  SDL_DestroyRenderer(this->renderer); 
}

void DEAD_Renderer::render() {
  this->renderMapObjects();
}
  
void DEAD_Renderer::renderMapObjects() {
  SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
  SDL_RenderClear(this->renderer);

  SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 0);
  SDL_RenderCopy(this->renderer, this->mapObjectTexture, &WOOD_LOCATION_RECT, &renderRect);
  
  SDL_RenderPresent(this->renderer);
}


