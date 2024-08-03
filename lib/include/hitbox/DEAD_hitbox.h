#pragma once
#include "../DEAD_map.h"

class DEAD_HitBox {
public:
  virtual bool pointInHitbox(DEAD_Map::MapLocation loc);
};
