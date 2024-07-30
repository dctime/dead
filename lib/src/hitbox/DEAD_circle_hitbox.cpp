#include "DEAD_map.h"
#include <cmath>
#include <hitbox/DEAD_circle_hitbox.h>
#include <iostream>
#include <memory>

DEAD_CircleHitbox::DEAD_CircleHitbox(double radius, DEAD_Map::MapLocation loc)
    : radius(radius), loc(loc) {}
double DEAD_CircleHitbox::getRadius() { return this->radius; }
DEAD_Map::MapLocation DEAD_CircleHitbox::getLoc() { return this->loc; }
void DEAD_CircleHitbox::setLoc(DEAD_Map::MapLocation newLoc) {
  this->loc = newLoc;
}

bool DEAD_CircleHitbox::iscollideWithCircle(
    DEAD_CircleHitbox* circleHitbox) {
  DEAD_Map::MapLocation locThis = this->loc;
  DEAD_Map::MapLocation locThat = circleHitbox->getLoc();

  double distance =
      sqrt(pow(locThis.x - locThat.x, 2) + pow(locThis.y - locThat.y, 2));
  if (distance <= this->radius + circleHitbox->getRadius()) {
    return true;
  } else {
    return false;
  }
}

void DEAD_CircleHitbox::setRadius(double radius) {
  this->radius = radius;
}
