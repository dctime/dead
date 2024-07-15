#include "map_objects/DEAD_map_object_base.h"
#include <SDL2/SDL_log.h>
#include <map_objects/DEAD_wood.h>
#include <SDL2/SDL.h>
DEAD_Wood::DEAD_Wood(DEAD_Map::MapLocation loc) 
  : DEAD_MapObjectBase(loc) {
  SDL_Log("init wood");
}

char DEAD_Wood::getChar() { return 'w'; }
