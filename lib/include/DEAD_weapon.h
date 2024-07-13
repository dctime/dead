#pragma once

#include <string>
#include <SDL2/SDL.h>

class DEAD_Weapon {
public:
  virtual SDL_Rect getTextureRect() = 0;
};
