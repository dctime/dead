#pragma once

#include "DEAD_hitbox.h"
#include "../DEAD_map.h"

class DEAD_CircleHitbox : public DEAD_HitBox {
public:
  DEAD_CircleHitbox(double radius, DEAD_Map::MapLocation loc);
  double getRadius();
  void setRadius(double radius);
  DEAD_Map::MapLocation getLoc();
  void setLoc(DEAD_Map::MapLocation newLoc);
  bool iscollideWithCircle(DEAD_CircleHitbox* circleHitbox);
  bool pointInHitbox(DEAD_Map::MapLocation loc) override;
private:
  double radius;
  DEAD_Map::MapLocation loc;
};
