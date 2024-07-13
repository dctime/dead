#pragma once

#include "DEAD_weapon.h"

class DEAD_Guns : public DEAD_Weapon {
public:
  DEAD_Guns();
  DEAD_Guns(DEAD_Player* player);
  virtual SDL_Rect getTextureRect() override = 0;
  virtual void shoot();
};
