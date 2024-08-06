#include "DEAD_item.h"
#include "DEAD_item_drop.h"
#include "DEAD_player.h"
#include <DEAD_item_drop_layer.h>
#include <climits>
#include <cmath>
#include <functional>
#include <guns/DEAD_pistol.h>
#include <iostream>
#include <memory>
#include <weapons/DEAD_bat.h>

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
    DEAD_Player *player, DEAD_Map::MapLocation loc, double radius,
    std::shared_ptr<DEAD_Item> &returnItem) {
  double minDistance = -1;
  std::shared_ptr<DEAD_ItemDrop> nearestItemDrop = nullptr;

  for (const std::shared_ptr<DEAD_ItemDrop> &itemDrop : this->itemDrops) {
    std::function<double(DEAD_Map::MapLocation, DEAD_Map::MapLocation)>
        calDistance =
            [](DEAD_Map::MapLocation loc1, DEAD_Map::MapLocation loc2) {
              return sqrt(pow(loc1.x - loc2.x, 2) + pow(loc1.y - loc2.y, 2));
            };
    double distance = calDistance(itemDrop->getLoc(), loc);
    if (distance <= radius && (minDistance == -1 || minDistance > distance)) {
      nearestItemDrop = itemDrop;
      minDistance = distance;
    }
  }
  if (nearestItemDrop == nullptr) {
    returnItem = nullptr;
    return;
  }
  returnItem = nearestItemDrop->getItem();
  this->itemDrops.erase(nearestItemDrop);
  returnItem->setPlayer(player);
}
