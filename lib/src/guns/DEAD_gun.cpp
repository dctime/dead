#include <DEAD_weapon.h>
#include <guns/DEAD_gun.h>
#include <bullets/DEAD_normal_bullet.h>
#include <iostream>
#include <memory>

DEAD_Gun::DEAD_Gun(std::shared_ptr<DEAD_Player> player, int magazineSize)
  : DEAD_Weapon(player), magazineSize(magazineSize) {
  this->ammoLeftInMagazine = this->magazineSize;
}


DEAD_Gun::~DEAD_Gun() {}


bool DEAD_Gun::removeAmmoFromMagazine(int count) {
  if (this->ammoLeftInMagazine < count) return false;
  this->ammoLeftInMagazine -= count;
  std::cout << "Ammo Left: " << this->ammoLeftInMagazine << std::endl;
  return true;
}

int DEAD_Gun::getAmmoLeftInMagazine() {
  return this->ammoLeftInMagazine;
}

void DEAD_Gun::insertNewMagazine() {
  this->ammoLeftInMagazine = this->magazineSize;
}

int DEAD_Gun::getMagazineSize() {
  return this->magazineSize; 
}

void DEAD_Gun::reload() {
  this->ammoLeftInMagazine = this->magazineSize;
  std::cout << "Gun Reloaded" << std::endl;
}


