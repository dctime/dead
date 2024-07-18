#include "DEAD_item_drop.h"
#include <DEAD_item_drop_layer.h>
#include <cmath>
#include <functional>
#include <iostream>
#include <memory>

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

void DEAD_ItemDropLayer::getNearItemDrop(DEAD_Map::MapLocation loc, double radius, std::shared_ptr<DEAD_Item>& returnItem) {
  for (std::shared_ptr<DEAD_ItemDrop> itemDrop : this->itemDrops) {
    std::function<double(DEAD_Map::MapLocation, DEAD_Map::MapLocation)>
        calDistance =
            [](DEAD_Map::MapLocation loc1, DEAD_Map::MapLocation loc2) {
              return sqrt(pow(loc1.x - loc2.x, 2) + pow(loc1.y - loc2.y, 2));
            };
    std::cout << "item: " << itemDrop->getLoc().x << ", " << itemDrop->getLoc().y;
    std::cout << "  Player: " << loc.x << ", " << loc.y << std::endl; 
    if (calDistance(itemDrop->getLoc(), loc) <= radius) {
      std::cout << "Pick That UP!" << std::endl;
      returnItem = itemDrop->getItem();
      this->itemDrops.erase(itemDrop);
      break;
    }
  }
}
