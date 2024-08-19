#include "map_objects/DEAD_map_object_base.h"
#include <SDL2/SDL_rect.h>
#include <map_objects/DEAD_stone.h>
#include <memory>


DEAD_Stone::DEAD_Stone(DEAD_Map::MapLocation loc) :
  DEAD_MapObjectBase(loc), memoryManager(std::make_unique<DEAD_PlayerMemoriableManager>()) {}
char DEAD_Stone::getChar() { return 's'; }
bool DEAD_Stone::isPlayerCollidable() { return true; }
bool DEAD_Stone::isZombieCollidable() { return true; }
SDL_Rect DEAD_Stone::getTextureRect() {
  SDL_Rect rect = {.x = 0, .y = 0, .w = 100, .h = 100};
  return rect;
}

DEAD_PlayerMemoriableManager * DEAD_Stone::getMemoryManager() {
  return this->memoryManager.get();
}


