#include "map_objects/DEAD_map_object_base.h"
#include <SDL2/SDL_rect.h>
#include <map_objects/DEAD_mid_road.h>

DEAD_MidRoad::DEAD_MidRoad(DEAD_Map::MapLocation loc) : 
  DEAD_MapObjectBase(loc) {

}
char DEAD_MidRoad::getChar() { return 'f'; }
bool DEAD_MidRoad::isPlayerCollidable() { return false; }
bool DEAD_MidRoad::isZombieCollidable() { return false; }
SDL_Rect DEAD_MidRoad::getTextureRect() { return {.x=0, .y=100, .w=100, .h=100}; }

std::string DEAD_MidRoad::getName() {
  return "Road";
}
std::string DEAD_MidRoad::getNote() {
  return "";
}

