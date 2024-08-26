#pragma once
#include <SDL2/SDL_video.h>
#include "DEAD_renderer.h"

class DEAD_Game;

class DEAD_Renderer3D {
public:
  DEAD_Renderer3D(SDL_Window* window, DEAD_Renderer* renderer, DEAD_Game* game); 
  ~DEAD_Renderer3D();
  void render();
  void renderMinimap();
  void renderFirstLayer();

private:
  SDL_Window* window;
  DEAD_Renderer* renderer;
  DEAD_Game* game;
  int minimapWidth;
  int minimapHeight;
  SDL_Texture* minimapTexture;
  int horizontalFOV;
  double heightForHalfFullInOneMapBlock;
  double maxRenderDistance;
  SDL_Texture* playerViewLayerTexture;
  double blockRenderHeight;
  SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
};
