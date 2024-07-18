#include "DEAD_item_drop.h"
#include <DEAD_game.h>
#include <guns/DEAD_pistol.h>
#include <bullets/DEAD_normal_bullet.h>
#include <SDL2/SDL_log.h>
#include <iostream>
#include <memory>

DEAD_Pistol::DEAD_Pistol(DEAD_Player* player)
: DEAD_Gun(player) {}

DEAD_Pistol::~DEAD_Pistol() {
  SDL_Log("Destroyed A Pistol");
}

SDL_Rect DEAD_Pistol::getTextureRect() {
  SDL_Rect rect = {.x=100, .y=0, .w=100, .h=100};
  return rect;
}

void DEAD_Pistol::attack() {
  DEAD_Bullet* bullet = new DEAD_NormalBullet(this->getPlayer(), this);
  std::cout << this->getPlayer()->getGame()->getBulletDirector()->bulletCount() << std::endl;
}

double DEAD_Pistol::getBarrelLength() {
  return 0.4;
}

std::shared_ptr<DEAD_ItemDrop> DEAD_Pistol::getItemDrop() {
  if (this->itemDrop == nullptr) {
    this->itemDrop = std::make_shared<DEAD_ItemDrop>(shared_from_this());
  }

  return this->itemDrop;
    
}
