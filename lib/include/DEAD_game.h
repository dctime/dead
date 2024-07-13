#pragma once

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include "DEAD_map.h"
#include "DEAD_renderer.h"
#include "DEAD_player.h"
#include "DEAD_controllable_player.h"
#include "DEAD_bullet_director.h"

class DEAD_Game {
public:
  DEAD_Game(DEAD_ControllablePlayer* player);
  ~DEAD_Game();
  void tick();
  void run();
  DEAD_Map* getMap();
  DEAD_Player* getPlayer();
  DEAD_Renderer* getRenderer();
  DEAD_BulletDirector* getBulletDirector();
  const int SCREEN_WIDTH = 720;
  const int SCREEN_HEIGHT = 480;
private:
  SDL_Window* window;
  DEAD_Map* map;
  DEAD_ControllablePlayer* player;
  void eventHandle();
  bool running = true;
  DEAD_Renderer* renderer;
  DEAD_BulletDirector* bulletDirector;
};
