#include "DEAD_item_drop.h"
#include <DEAD_game.h>
#include <DEAD_player.h>
#include <DEAD_weapon.h>
#include <guns/DEAD_pistol.h>
#include <SDL2/SDL_log.h>
#include <memory>

DEAD_Player::DEAD_Player(DEAD_Game* game) 
  : DEAD_Entity::DEAD_Entity(game, 10000, 0.8),
  inventory(std::make_unique<DEAD_PlayerInventory>(this)) {
}

void DEAD_Player::setHoldItem(std::shared_ptr<DEAD_Item> item) {
  this->holdItem = item;
}

DEAD_Player::~DEAD_Player() {}

void DEAD_Player::move(double x, double y) {
  if (this->getGame()->getCollisionDirector()->playerCheckCollision(this, x, y).size() != 0) {
    return;
  } else {
    this->setPos(this->getPos().x+x, this->getPos().y+y);
  }
}

void DEAD_Player::pickupOrDrop() {
  if (this->holdItem != nullptr) {
    this->dropHoldItem();
  } else {
    this->pickupItem();
  }

}
void DEAD_Player::dropHoldItem() {
  this->inventory->dropHoldItem(); 
}

void DEAD_Player::pickupItem() {
  std::shared_ptr<DEAD_Item> tempItem;
  this->getGame()->getItemDropLayer()->getNearItemDrop(this, this->getPos(), this->getPickItemRadius(), tempItem);
  SDL_Log("Picked Up Weapon");
  if (tempItem == nullptr) return;
  tempItem->unbindItemDrop();
  this->inventory->replaceHoldItem(tempItem);
}

SDL_Rect DEAD_Player::getTextureRect() {
  const std::shared_ptr<DEAD_Item>& item = std::dynamic_pointer_cast<DEAD_Item>(this->holdItem);
  if (item == nullptr) {
    SDL_Rect rect = {.x = 0, .y = 0, .w = 100, .h = 100};
    return rect;
  }
  
  return item->getTextureRect();
}

void DEAD_Player::attack() {
  const std::shared_ptr<DEAD_Weapon>& weapon = std::dynamic_pointer_cast<DEAD_Weapon>(this->holdItem);
  if (weapon == nullptr) {
    return;
  }
  weapon->attack();
}

void DEAD_Player::reloadGun() {
  const std::shared_ptr<DEAD_Gun>& gun = std::dynamic_pointer_cast<DEAD_Gun>(this->holdItem);
  if (gun == nullptr) {
    return;
  }

  gun->reload();
}

void DEAD_Player::useItem() {
  if (this->holdItem == nullptr) return;
  this->holdItem->use();
}
