#include "DEAD_functions.h"
#include "items/DEAD_item.h"
#include "DEAD_item_drop.h"
#include "DEAD_player.h"
#include <DEAD_item_drop_layer.h>
#include <climits>
#include <cmath>
#include <items/weapons/guns/DEAD_pistol.h>
#include <iostream>
#include <memory>
#include <items/weapons/DEAD_bat.h>

DEAD_ItemDropLayer::DEAD_ItemDropLayer() {
  this->itemDrops.size();

  std::cout << "itemDropLayer Created" << std::endl;
}

std::set<std::shared_ptr<DEAD_ItemDrop>> DEAD_ItemDropLayer::getItemDrops() {
  return this->itemDrops;
}

void DEAD_ItemDropLayer::drop(std::shared_ptr<DEAD_ItemDrop> itemDrop) {
  this->itemDrops.insert(itemDrop);
}

int DEAD_ItemDropLayer::getDropsCount() { return this->itemDrops.size(); }

void DEAD_ItemDropLayer::getNearItemDrop(
    DEAD_Map::MapLocation loc, double radius,
    std::shared_ptr<DEAD_ItemDrop> &returnItemDrop) {
  double minDistance = -1;
  returnItemDrop = nullptr;
  for (const std::shared_ptr<DEAD_ItemDrop> &itemDrop : this->itemDrops) {
    double distance = DEAD_Functions::calDistance(itemDrop->getLoc().x, itemDrop->getLoc().y, loc.x, loc.y);
    if (distance <= radius && (minDistance == -1 || minDistance > distance)) {
      returnItemDrop = itemDrop;
      minDistance = distance;
    }
  }
}

void DEAD_ItemDropLayer::getAndPickupNearItemDrop(
    DEAD_Player *player, DEAD_Map::MapLocation loc, double radius,
    std::shared_ptr<DEAD_Item> &returnItem) {
  std::shared_ptr<DEAD_ItemDrop> nearestItemDrop;
  this->getNearItemDrop(loc, radius, nearestItemDrop);

  if (nearestItemDrop == nullptr) {
    returnItem = nullptr;
    return;
  }
  returnItem = nearestItemDrop->getItem();
  this->itemDrops.erase(nearestItemDrop);
  returnItem->setPlayer(player);
}
