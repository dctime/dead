#include <hitbox/DEAD_rect_hitbox.h>

DEAD_RectHitbox::DEAD_RectHitbox(DEAD_Map::MapLocation leftUpLoc, double width, double height) 
  : leftUpLoc(leftUpLoc), width(width), height(height) {
}

double DEAD_RectHitbox::getWidth() { return this->width; }
double DEAD_RectHitbox::getHeight() { return this->height; }



