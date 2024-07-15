#pragma once

#include "DEAD_hitbox.h"
#include "../DEAD_map.h"

class DEAD_RectHitbox : public DEAD_HitBox {
public:
  DEAD_RectHitbox(DEAD_Map::MapLocation leftUpLoc, double width, double height);
  double getWidth();
  double getHeight();
private:
  DEAD_Map::MapLocation leftUpLoc;
  double width;
  double height;
};
