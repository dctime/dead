#include <map_objects/DEAD_map_object_base.h>
#include <DEAD_map.h>

DEAD_MapObjectBase::DEAD_MapObjectBase(DEAD_Map::MapLocation loc) {
  this->leftUpLoc = loc;  
};

DEAD_Map::MapLocation DEAD_MapObjectBase::getLeftUpLoc() { return this->leftUpLoc; }

