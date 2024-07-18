#include <DEAD_item_drop.h>
#include <SDL2/SDL_log.h>
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
