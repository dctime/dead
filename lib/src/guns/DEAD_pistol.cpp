#include "DEAD_item_drop.h"
#include "bullets/DEAD_bullet.h"
#include <DEAD_game.h>
#include <guns/DEAD_pistol.h>
#include <bullets/DEAD_normal_bullet.h>
#include <SDL2/SDL_log.h>
#include <iostream>
#include <memory>

DEAD_Pistol::DEAD_Pistol(DEAD_Player* player)
: DEAD_Gun(player, 10, 500, 2000) {}

DEAD_Pistol::~DEAD_Pistol() {
  SDL_Log("Destroyed A Pistol");
}

SDL_Rect DEAD_Pistol::getTextureRect() {
  SDL_Rect rect = {.x=100, .y=0, .w=100, .h=100};
  return rect;
}

void DEAD_Pistol::attack() {

  if (this->checkStillCooling() != 1.0 || this->checkStillReloading() != 1.0) {
    return;
  }

  if (!this->removeAmmoFromMagazine(1)) {
    return;
  }

  std::unique_ptr<DEAD_Bullet> bullet = 
    std::make_unique<DEAD_NormalBullet>(this->getPlayer(), this);
  this->getPlayer()->getGame()->getBulletDirector()->registerBullet(bullet);
  this->startCoolDown();
  this->getPlayer()->getGame()->getSoundDirector()->playPistolShootSound();
}

void DEAD_Pistol::reload() {
  this->insertNewMagazine();
  this->startReload();
  this->getPlayer()->getGame()->getSoundDirector()->playPistolReloadSound();
}

double DEAD_Pistol::getBarrelLength() {
  return 0.4;
}



int DEAD_Pistol::getMagazineSize() {
  return 10;
}

SDL_Rect DEAD_Pistol::getItemTextureRect() {
  SDL_Rect rect = {.x=0, .y=0, .w=100, .h=100};
  return rect;
}
