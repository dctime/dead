#include <hitbox/DEAD_circle_hitbox.h>

DEAD_CircleHitbox::DEAD_CircleHitbox(double radius, DEAD_Map::MapLocation loc)
  : radius(radius), loc(loc) {

}
double DEAD_CircleHitbox::getRadius() { return this->radius; }
DEAD_Map::MapLocation DEAD_CircleHitbox::getLoc() { return this->loc; }
void DEAD_CircleHitbox::setLoc(DEAD_Map::MapLocation newLoc) {
  this->loc = newLoc;
}
