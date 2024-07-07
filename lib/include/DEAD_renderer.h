#pragma once

#include <SDL2/SDL_render.h>

class DEAD_Game;

class DEAD_Renderer {
public:
  DEAD_Renderer();
  DEAD_Renderer(SDL_Window* window, DEAD_Game* game);
  ~DEAD_Renderer();
  void render();
  static const SDL_Rect STONE_LOCATION_RECT;
  static const SDL_Rect WOOD_LOCATION_RECT;
private:
  void renderMapObjects();
  SDL_Renderer* renderer;
  int renderBlockSize = 30;
  struct RenderAnchor {
    double x;
    double y;
  };
  
  RenderAnchor renderAnchor = {.x=0, .y=0};
  SDL_Rect renderRect = {.x=0, .y=0, .w=renderBlockSize, .h=renderBlockSize};
  SDL_Texture *mapObjectTexture;


};
