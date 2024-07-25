#include "DEAD_weapon.h"
#include <memory>
#include <weapons/DEAD_bat.h>
#include <DEAD_player.h>

DEAD_Bat::DEAD_Bat(std::shared_ptr<DEAD_Player> owner) :
  DEAD_Weapon(owner) {

}

void DEAD_Bat::attack() {}

SDL_Rect DEAD_Bat::getTextureRect() {
  SDL_Rect rect = {.x=200, .y=0, .w=100, .h=100};
  return rect;
}

SDL_Rect DEAD_Bat::getItemTextureRect() {
  SDL_Rect rect = {.x=100, .y=0, .w=100, .h=100};
  return rect;
}

std::shared_ptr<DEAD_ItemDrop> DEAD_Bat::getItemDrop() {
  if (this->itemDrop == nullptr) {
    this->itemDrop = std::make_shared<DEAD_ItemDrop>(shared_from_this(), this->getPlayer()->getPos());
  }

  return this->itemDrop;
}
