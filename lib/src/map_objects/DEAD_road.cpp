#include "map_objects/DEAD_map_object_base.h"
#include <SDL2/SDL_rect.h>
#include <map_objects/DEAD_road.h>

DEAD_Road::DEAD_Road(DEAD_Map::MapLocation loc) : 
  DEAD_MapObjectBase(loc) {

}
char DEAD_Road::getChar() { return 'f'; }
bool DEAD_Road::isPlayerCollidable() { return false; }
bool DEAD_Road::isZombieCollidable() { return false; }
SDL_Rect DEAD_Road::getTextureRect() { return {.x=400, .y=0, .w=100, .h=100}; }

