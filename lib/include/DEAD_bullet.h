#pragma once

#include "DEAD_player.h"
#include <SDL2/SDL.h>

class DEAD_Bullet {
public:
  DEAD_Bullet(DEAD_Player* owner);
  virtual SDL_Rect getBulletTextureRect() = 0;
private:
  DEAD_Player* owner;
  DEAD_Player::Position pos;
};
