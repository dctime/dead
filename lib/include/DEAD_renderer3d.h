#pragma once
#include <SDL2/SDL_video.h>
#include "DEAD_renderer.h"

class DEAD_Game;

class DEAD_Renderer3D {
public:
  DEAD_Renderer3D(SDL_Window* window, DEAD_Renderer* renderer, DEAD_Game* game); 
  void render();
  void renderMinimap();
private:
  SDL_Window* window;
  DEAD_Renderer* renderer;
  DEAD_Game* game;
};
