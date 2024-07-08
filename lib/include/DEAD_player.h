#pragma once

#include <SDL2/SDL_render.h>

class DEAD_Game;

class DEAD_Player {
public:
  DEAD_Player(DEAD_Game* game);
  ~DEAD_Player();
private:
  DEAD_Game* game;
  SDL_Texture* playerTexture;
};
