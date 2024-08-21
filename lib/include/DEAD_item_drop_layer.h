#pragma once

#include "DEAD_item_drop.h"
#include "DEAD_player.h"
#include <memory>
#include <set>
class DEAD_ItemDropLayer {
public:
  DEAD_ItemDropLayer();
  std::set<std::shared_ptr<DEAD_ItemDrop>> getItemDrops();
  void drop(std::shared_ptr<DEAD_ItemDrop> itemDrop);
  int getDropsCount();
  void getAndPickupNearItemDrop(DEAD_Player *player, DEAD_Map::MapLocation loc,
                                double radius,
                                std::shared_ptr<DEAD_Item> &returnItem);
  void getNearItemDrop(DEAD_Map::MapLocation loc, double radius,
                       std::shared_ptr<DEAD_ItemDrop> &returnItemDrop);

  template <typename T> void summonItemDrop(double x, double y) {
    std::shared_ptr<DEAD_Item> summonItem = std::make_shared<T>(nullptr);
    this->drop(summonItem->getItemDrop(x, y));
  }

private:
  std::set<std::shared_ptr<DEAD_ItemDrop>> itemDrops;
};
