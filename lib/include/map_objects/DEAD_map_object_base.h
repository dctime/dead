#pragma once
#include "../DEAD_map.h"
#include "../hitbox/DEAD_rect_hitbox.h"

class DEAD_MapObjectBase {
public:
  DEAD_MapObjectBase(DEAD_Map::MapLocation loc);
  ~DEAD_MapObjectBase();
  virtual char getChar() = 0;
  DEAD_RectHitbox* getHitBox();
  DEAD_Map::MapLocation getLeftUpLoc();
private:
  DEAD_Map::MapLocation leftUpLoc;
  DEAD_RectHitbox* hitbox;  
};
