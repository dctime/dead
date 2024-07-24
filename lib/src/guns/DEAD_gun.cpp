#include <DEAD_weapon.h>
#include <SDL2/SDL_timer.h>
#include <guns/DEAD_gun.h>
#include <bullets/DEAD_normal_bullet.h>
#include <iostream>
#include <memory>

DEAD_Gun::DEAD_Gun(std::shared_ptr<DEAD_Player> player, const int MAGAZINE_SIZE, const int COOLDOWN_TIME, const int RELOAD_TIME)
  : DEAD_Weapon(player), MAGAZINE_SIZE(MAGAZINE_SIZE), COOLDOWN_TIME(COOLDOWN_TIME), RELOAD_TIME(RELOAD_TIME),
    startReloadTicks(0), startCoolingTicks(0) {
  this->ammoLeftInMagazine = this->MAGAZINE_SIZE;
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
  this->ammoLeftInMagazine = this->MAGAZINE_SIZE;
}

int DEAD_Gun::getMagazineSize() {
  return this->MAGAZINE_SIZE; 
}

void DEAD_Gun::reload() {
  this->ammoLeftInMagazine = this->MAGAZINE_SIZE;
  this->startReload();
  std::cout << "Gun Reloaded" << std::endl;
}

void DEAD_Gun::startCoolDown() {
  this->startCoolingTicks = SDL_GetTicks64();
}

void DEAD_Gun::startReload() {
  this->startReloadTicks = SDL_GetTicks64();
}

// 0.0 - 1.0, means not cooling;
double DEAD_Gun::checkStillCooling() {
  int nowTicks = SDL_GetTicks64();
  int coolingTicks = nowTicks - this->startCoolingTicks;
  if (coolingTicks >= this->COOLDOWN_TIME) return 1.0;
  else return static_cast<double>(coolingTicks) / this->COOLDOWN_TIME;
}

double DEAD_Gun::checkStillReloading() {
  int nowTicks = SDL_GetTicks64();
  int reloadingTicks = nowTicks - this->startReloadTicks;
  if (reloadingTicks >= this->RELOAD_TIME) return 1.0;
  else return static_cast<double>(reloadingTicks) / this->RELOAD_TIME;
}







