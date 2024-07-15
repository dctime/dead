#include <map_objects/DEAD_map_object_base.h>
#include <DEAD_map.h>
#include <hitbox/DEAD_rect_hitbox.h>

DEAD_MapObjectBase::DEAD_MapObjectBase(DEAD_Map::MapLocation loc) : 
  leftUpLoc(loc), hitbox(new DEAD_RectHitbox(this->leftUpLoc, 1.0, 1.0)) {
};

DEAD_MapObjectBase::~DEAD_MapObjectBase() {
  delete this->hitbox;
}

DEAD_Map::MapLocation DEAD_MapObjectBase::getLeftUpLoc() { return this->leftUpLoc; }
DEAD_RectHitbox* DEAD_MapObjectBase::getHitBox() { return this->hitbox; }
