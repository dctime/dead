#pragma once

#include <string>
#include <SDL2/SDL.h>

class DEAD_Player;

class DEAD_Weapon {
public:
  DEAD_Weapon(DEAD_Player* owner);
  virtual SDL_Rect getTextureRect() = 0;
  DEAD_Player* getPlayer();
  virtual void attack() = 0;
private:
  DEAD_Player* owner;
};
