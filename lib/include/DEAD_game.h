#pragma once

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include "DEAD_map.h"
#include "DEAD_renderer.h"
#include "DEAD_player.h"

class DEAD_Game {
public:
  DEAD_Game();
  ~DEAD_Game();
  void tick();
  void run();
  DEAD_Map* getMap();
  SDL_Renderer* getRenderer();
  SDL_Window* getWindow();
  const int SCREEN_WIDTH = 720;
  const int SCREEN_HEIGHT = 480;
private:
  SDL_Window* window;
  DEAD_Map* map;
  void eventHandle();
  bool running = true;
  SDL_Renderer* renderer;
  DEAD_Renderer* deadRenderer;
};
