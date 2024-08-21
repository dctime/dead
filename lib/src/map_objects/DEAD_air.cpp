#include "map_objects/DEAD_map_object_base.h"
#include <SDL2/SDL_rect.h>
#include <map_objects/DEAD_air.h>

DEAD_Air::DEAD_Air(DEAD_Map::MapLocation loc) : 
  DEAD_MapObjectBase(loc) {

}
char DEAD_Air::getChar() { return ' '; }
bool DEAD_Air::isPlayerCollidable() { return false; }
bool DEAD_Air::isZombieCollidable() { return false; }

std::string DEAD_Air::getName() {
  return "Air";
}

std::string DEAD_Air::getNote() {
  return "";
}

