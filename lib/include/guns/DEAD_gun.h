#pragma once

#include "../DEAD_weapon.h"
#include <memory>

class DEAD_Gun : public DEAD_Weapon {
public:
  DEAD_Gun(std::shared_ptr<DEAD_Player> player, int magazineSize);
  ~DEAD_Gun();
  virtual SDL_Rect getTextureRect() override = 0;
  virtual void attack() override = 0;
  virtual double getBarrelLength() = 0;
  virtual std::shared_ptr<DEAD_ItemDrop> getItemDrop() override = 0;
  virtual SDL_Rect getItemTextureRect() override = 0;
  int getMagazineSize();
  bool removeAmmoFromMagazine(int count);
  int getAmmoLeftInMagazine();
  void insertNewMagazine();
  void reload();
private:
  int ammoLeftInMagazine;
  const int magazineSize;
};
