#pragma once

#include <SDL2/SDL_render.h>

class DEAD_Renderer {
public:
  DEAD_Renderer();
  DEAD_Renderer(SDL_Window* window);
  ~DEAD_Renderer();
  void render();
  static const SDL_Rect STONE_LOCATION_RECT;
  static const SDL_Rect WOOD_LOCATION_RECT;
private:
  void renderMapObjects();

  SDL_Renderer* renderer;
  double renderBlockSize;
  struct renderAnchor {
    double x;
    double y;
  };
  
  SDL_Rect renderRect = {.x=10, .y=10, .w=30, .h=30};
  SDL_Texture *mapObjectTexture;


};
