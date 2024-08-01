#include "DEAD_item_drop.h"
#include <DEAD_item.h>
#include <memory>
#include <DEAD_player.h>

DEAD_Item::DEAD_Item(DEAD_Player* owner) 
  : itemDrop(nullptr) {
  this->owner = owner;
}

DEAD_Item::~DEAD_Item() {}
void DEAD_Item::unbindItemDrop() {
  this->itemDrop = nullptr;
}

DEAD_Player* DEAD_Item::getPlayer() {
  return this->owner;
}

void DEAD_Item::setPlayer(DEAD_Player* player) {
  this->owner = player;
}

std::shared_ptr<DEAD_ItemDrop> DEAD_Item::getItemDrop() {
  if (this->itemDrop == nullptr) {
    this->itemDrop = std::make_shared<DEAD_ItemDrop>(shared_from_this(), this->getPlayer()->getPos());
  }

  return this->itemDrop;
}

std::shared_ptr<DEAD_ItemDrop> DEAD_Item::getItemDrop(double x, double y) {
  DEAD_Map::MapLocation loc = {.x=x, .y=y};
  this->itemDrop = std::make_shared<DEAD_ItemDrop>(shared_from_this(), loc);

  return this->itemDrop;
}
