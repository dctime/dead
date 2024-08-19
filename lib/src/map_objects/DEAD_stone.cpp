#include "map_objects/DEAD_map_object_base.h"
#include <SDL2/SDL_rect.h>
#include <map_objects/DEAD_stone.h>


DEAD_Stone::DEAD_Stone(DEAD_Map::MapLocation loc) :
  DEAD_MapObjectBase(loc), visible(false) {}
char DEAD_Stone::getChar() { return 's'; }
bool DEAD_Stone::isPlayerCollidable() { return true; }
bool DEAD_Stone::isZombieCollidable() { return true; }
SDL_Rect DEAD_Stone::getTextureRect() {
  SDL_Rect rect = {.x = 0, .y = 0, .w = 100, .h = 100};
  return rect;
}

bool DEAD_Stone::isVisible() {
  return this->visible;
}

void DEAD_Stone::setToVisible() {
  this->visible = true;
}

