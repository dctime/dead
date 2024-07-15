#include "map_objects/DEAD_map_object_base.h"
#include <map_objects/DEAD_stone.h>


DEAD_Stone::DEAD_Stone(DEAD_Map::MapLocation loc) :
  DEAD_MapObjectBase(loc){}
char DEAD_Stone::getChar() { return 's'; }
