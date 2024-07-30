#pragma once

#include "DEAD_hitbox.h"
#include "DEAD_circle_hitbox.h"
#include "../DEAD_map.h"
#include <memory>

class DEAD_RectHitbox : public DEAD_HitBox {
public:
  DEAD_RectHitbox(DEAD_Map::MapLocation leftUpLoc, double width, double height);
  double getWidth();
  double getHeight();
  bool isCollideWithCircle(DEAD_CircleHitbox* circleHitbox);
  bool isCollideWithCircle(DEAD_Map::MapLocation midLocCircle, double radius);
private:
  DEAD_Map::MapLocation leftUpLoc;
  double width;
  double height;
};
