#include "DEAD_item_drop.h"
#include "bullets/DEAD_bullet.h"
#include <DEAD_game.h>
#include <guns/DEAD_pistol.h>
#include <bullets/DEAD_normal_bullet.h>
#include <SDL2/SDL_log.h>
#include <iostream>
#include <memory>

DEAD_Pistol::DEAD_Pistol(std::shared_ptr<DEAD_Player> player)
: DEAD_Gun(player, 10, 1000, 3000) {}

DEAD_Pistol::~DEAD_Pistol() {
  SDL_Log("Destroyed A Pistol");
}

SDL_Rect DEAD_Pistol::getTextureRect() {
  SDL_Rect rect = {.x=100, .y=0, .w=100, .h=100};
  return rect;
}

void DEAD_Pistol::attack() {

  if (this->checkStillCooling() != 1.0 || this->checkStillReloading() != 1.0) {
    std::cout << "Pistol Cooling" << std::endl;
    return;
  }

  if (!this->removeAmmoFromMagazine(1)) {
    std::cout << "No ammo left in magazine" << std::endl;
    return;
  }

  std::shared_ptr<DEAD_Bullet> bullet = 
    std::make_shared<DEAD_NormalBullet>(this->getPlayer(), std::static_pointer_cast<DEAD_Pistol>(DEAD_Pistol::shared_from_this()));
  bullet->registerBullet();
  this->startCoolDown();
  std::cout << "Bullet Count: " << this->getPlayer()->getGame()->getBulletDirector()->bulletCount() << std::endl;
  this->getPlayer()->getGame()->getSoundDirector()->playPistolShootSound();
}

double DEAD_Pistol::getBarrelLength() {
  return 0.4;
}

std::shared_ptr<DEAD_ItemDrop> DEAD_Pistol::getItemDrop() {
  if (this->itemDrop == nullptr) {
    this->itemDrop = std::make_shared<DEAD_ItemDrop>(shared_from_this(), this->getPlayer()->getPos());
  }

  return this->itemDrop;
    
}

int DEAD_Pistol::getMagazineSize() {
  return 10;
}

SDL_Rect DEAD_Pistol::getItemTextureRect() {
  SDL_Rect rect = {.x=0, .y=0, .w=100, .h=100};
  return rect;
}
