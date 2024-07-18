#pragma once

#include "../DEAD_weapon.h"

class DEAD_Gun : public DEAD_Weapon {
public:
  DEAD_Gun(DEAD_Player* player);
  ~DEAD_Gun();
  virtual SDL_Rect getTextureRect() override = 0;
  virtual void attack() override = 0;
  virtual double getBarrelLength() = 0;
  virtual std::shared_ptr<DEAD_ItemDrop> getItemDrop() override = 0;
  virtual SDL_Rect getItemTextureRect() override = 0;
};
