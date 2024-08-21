#include "map_objects/DEAD_map_object_base.h"
#include <SDL2/SDL_rect.h>
#include <map_objects/DEAD_floor.h>

DEAD_Floor::DEAD_Floor(DEAD_Map::MapLocation loc) : 
  DEAD_MapObjectBase(loc) {

}
char DEAD_Floor::getChar() { return 'f'; }
bool DEAD_Floor::isPlayerCollidable() { return false; }
bool DEAD_Floor::isZombieCollidable() { return false; }
SDL_Rect DEAD_Floor::getTextureRect() { return {.x=300, .y=0, .w=100, .h=100}; }

std::string DEAD_Floor::getNote() {
  return "";
}

std::string DEAD_Floor::getName() {
  return "Floor";
}

