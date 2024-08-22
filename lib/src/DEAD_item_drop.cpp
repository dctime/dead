#include <DEAD_item_drop.h>
#include <SDL2/SDL_log.h>
#include <items/DEAD_item.h>
#include <memory>

DEAD_ItemDrop::DEAD_ItemDrop(std::shared_ptr<DEAD_Item> item, DEAD_Map::MapLocation loc)
  : item(item), loc(loc) {
  SDL_Log("Item Drop Created");
}

DEAD_Map::MapLocation DEAD_ItemDrop::getLoc() {
  return this->loc;
}

double DEAD_ItemDrop::getSize() {
  return 0.6;
}

std::shared_ptr<DEAD_Item> DEAD_ItemDrop::getItem() {
  return this->item;
}

std::string DEAD_ItemDrop::getName() {
  return this->item->getName();  
}

std::string DEAD_ItemDrop::getNote() {
  return this->item->getNote(); 
}

