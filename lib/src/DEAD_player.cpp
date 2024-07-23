#include "DEAD_item_drop.h"
#include <DEAD_game.h>
#include <DEAD_player.h>
#include <DEAD_weapon.h>
#include <guns/DEAD_pistol.h>
#include <SDL2/SDL_log.h>
#include <memory>

DEAD_Player::DEAD_Player(std::shared_ptr<DEAD_Game> game) : DEAD_Entity::DEAD_Entity(game, 100) {
}

DEAD_Player::~DEAD_Player() {}

void DEAD_Player::move(double x, double y) {
  if (this->getGame()->getCollisionDirector()->playerCheckCollision(std::dynamic_pointer_cast<DEAD_Player>(shared_from_this()), x, y).size() != 0) {
    return;
  } else {
    this->setPos(this->getPos().x+x, this->getPos().y+y);
  }
}

void DEAD_Player::summonPistol() {
  this->holdItem = std::make_shared<DEAD_Pistol>(std::static_pointer_cast<DEAD_Player>(DEAD_Entity::shared_from_this()));
}

void DEAD_Player::pickupOrDrop() {
  if (this->holdItem != nullptr) {
    this->dropWeapon();
  } else {
    this->pickupWeapon();
  }

}
void DEAD_Player::dropWeapon() {
  this->getGame()->getItemDropLayer()->drop(this->holdItem->getItemDrop());
  this->holdItem = nullptr;
  SDL_Log("Dropped Weapons Count: %d", this->getGame()->getItemDropLayer()->getDropsCount()); 
}

void DEAD_Player::pickupWeapon() {
  this->getGame()->getItemDropLayer()->getNearItemDrop(this->getPos(), this->getPickItemRadius(), this->holdItem);
  SDL_Log("Picked Up Weapon");
  if (this->holdItem == nullptr) return;
  this->holdItem->unbindItemDrop();
}

SDL_Rect DEAD_Player::getTextureRect() {
  std::shared_ptr<DEAD_Item> item = std::dynamic_pointer_cast<DEAD_Item>(this->holdItem);
  if (item == nullptr) {
    SDL_Rect rect = {.x = 0, .y = 0, .w = 100, .h = 100};
    return rect;
  }
  
  return item->getTextureRect();
}

void DEAD_Player::attack() {
  std::shared_ptr<DEAD_Weapon> weapon = std::dynamic_pointer_cast<DEAD_Weapon>(this->holdItem);
  if (weapon == nullptr) {
    return;
  }
  weapon->attack();
}
