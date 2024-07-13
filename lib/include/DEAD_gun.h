#pragma once

#include "DEAD_weapon.h"

class DEAD_Gun : public DEAD_Weapon {
public:
  DEAD_Gun();
  DEAD_Gun(DEAD_Player* player);
  virtual SDL_Rect getTextureRect() override = 0;
  virtual void shoot();
};
