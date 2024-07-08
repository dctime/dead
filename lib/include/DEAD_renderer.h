#pragma once

#include <SDL2/SDL_render.h>

class DEAD_Game;

struct RenderAnchor {
    double x;
    double y;
};

class DEAD_LocationRectMapObject {
public:
  static const SDL_Rect WOOD_LOCATION_RECT;
  static const SDL_Rect STONE_LOCATION_RECT;
};

class DEAD_Renderer {
public:
  DEAD_Renderer();
  DEAD_Renderer(SDL_Window* window, DEAD_Game* game);
  ~DEAD_Renderer();
  void render();
private:
  void renderMapObjects();
  SDL_Renderer* renderer;
  int renderBlockSize = 30;

  DEAD_Game* game;
  RenderAnchor renderAnchor = {.x=0, .y=0};
  SDL_Rect renderRect = {.x=0, .y=0, .w=renderBlockSize, .h=renderBlockSize};
  SDL_Texture *mapObjectTexture;
  SDL_Texture *playerTexture;


};
