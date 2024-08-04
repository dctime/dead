#include "DEAD_functions.h"
#include "DEAD_item_drop.h"
#include "decorations/DEAD_decoration_base.h"
#include "DEAD_controllable_player.h"
#include <DEAD_game.h>
#include <DEAD_player.h>
#include <DEAD_weapon.h>
#include <guns/DEAD_pistol.h>
#include <SDL2/SDL_log.h>
#include <iostream>
#include <memory>

DEAD_Player::DEAD_Player(DEAD_Game* game) 
  : DEAD_Entity::DEAD_Entity(game, 10000, 0.8),
  inventory(std::make_unique<DEAD_PlayerInventory>(this)),
  zombieKillcount(0) {
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

DEAD_PlayerInventory* DEAD_Player::getInventory() {
  return this->inventory.get();
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
  if (this->holdItem->use() == false) return;
  this->getInventory()->replaceHoldItem(nullptr);
}

void DEAD_Player::incrementZombieKillCount() {
  this->zombieKillcount++;
}

int DEAD_Player::getZombieKillCount() {
  return this->zombieKillcount;
}

void DEAD_Player::interactWithDecoration(int pressTimeInterval) {
  std::cout << "time Interval: " << pressTimeInterval << std::endl;
  DEAD_DecorationBase* interactingDeco = this->getDecorationInFrontof(1, 0.1);
  DEAD_ControllablePlayer* player = dynamic_cast<DEAD_ControllablePlayer*>(this);
  
  if (this->currentDestroyingDeco != interactingDeco) {
    this->currentDestroyingDeco = interactingDeco;
    // Reset Interval
    player->resetLastTimePressTicks();
  }

  if (interactingDeco == nullptr) return;
  if (player == nullptr) return;
  if (interactingDeco->destroying(pressTimeInterval, player)) {
    this->getGame()->getDecorationLayer()->deleteDeco(interactingDeco);
    player->resetLastTimePressTicks();
  }
}

DEAD_DecorationBase* DEAD_Player::getDecorationInFrontof(double range, double precision) {
  DEAD_Vector facingVector = DEAD_Functions::calUnitVector(this->getRotation());
  DEAD_Map::MapLocation playerLoc = this->getPos();
  for (double tempRange = 0; tempRange <= range; tempRange+=precision) {
    DEAD_Map::MapLocation checkingLoc = {.x=playerLoc.x + facingVector.x * tempRange, .y=playerLoc.y + facingVector.y * tempRange};
    DEAD_DecorationBase* returnDeco = this->getGame()->getDecorationLayer()->getFirstDecorationByLoc(checkingLoc);
    if (returnDeco != nullptr) return returnDeco;
  }
  return nullptr;
}

DEAD_DecorationBase* DEAD_Player::getCurrentDestoryingDeco() {
  DEAD_ControllablePlayer* player = dynamic_cast<DEAD_ControllablePlayer*>(this);
  if (player == nullptr) return nullptr;
  if (!player->getIsPressingUseKey()) return nullptr;
  return player->currentDestroyingDeco;
}



