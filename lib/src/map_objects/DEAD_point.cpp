#include "map_objects/DEAD_map_object_base.h"
#include <map_objects/DEAD_point.h>

DEAD_Point::DEAD_Point(DEAD_Map::MapLocation loc) : 
  DEAD_MapObjectBase(loc) {

}
char DEAD_Point::getChar() { return 'p'; }
bool DEAD_Point::isPlayerCollidable() { return false; }
bool DEAD_Point::isZombieCollidable() { return false; }
SDL_Rect DEAD_Point::getTextureRect() { return {.x=300, .y=0, .w=100, .h=100}; }

std::string DEAD_Point::getNote() {
  return "Where player spawns when the game starts";
}

std::string DEAD_Point::getName() {
  return "Spawn Point";
}

