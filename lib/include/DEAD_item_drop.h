#pragma once


#include "DEAD_map.h"
#include <memory>

class DEAD_Item;

class DEAD_ItemDrop {
public:
  DEAD_ItemDrop(std::shared_ptr<DEAD_Item> item, DEAD_Map::MapLocation loc);
  std::shared_ptr<DEAD_Item> getItem();
  DEAD_Map::MapLocation getLoc();
  double getSize();
  std::string getName();
  std::string getNote();
private:
  std::shared_ptr<DEAD_Item> item;
  DEAD_Map::MapLocation loc;
};
