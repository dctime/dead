#include "hitbox/DEAD_circle_hitbox.h"
#include <cmath>
#include <hitbox/DEAD_rect_hitbox.h>
#include <memory>

DEAD_RectHitbox::DEAD_RectHitbox(DEAD_Map::MapLocation leftUpLoc, double width, double height) 
  : leftUpLoc(leftUpLoc), width(width), height(height) {
}

double DEAD_RectHitbox::getWidth() { return this->width; }
double DEAD_RectHitbox::getHeight() { return this->height; }

bool DEAD_RectHitbox::isCollideWithCircle(DEAD_CircleHitbox* circleHitbox) {
  return isCollideWithCircle(circleHitbox->getLoc(), circleHitbox->getRadius());

}

bool DEAD_RectHitbox::isCollideWithCircle(DEAD_Map::MapLocation midLocCircle, double radius) {
  double testX = midLocCircle.x;
  double testY = midLocCircle.y;

  if (midLocCircle.x < this->leftUpLoc.x) testX = this->leftUpLoc.x;
  else if (midLocCircle.x > this->leftUpLoc.x + this->width) testX = this->leftUpLoc.x + this->width;

  if (midLocCircle.y < this->leftUpLoc.y) testY = this->leftUpLoc.y;
  else if (midLocCircle.y > this->leftUpLoc.y + this->height) testY = this->leftUpLoc.y + this->height;

  double distance = sqrt(pow((midLocCircle.x - testX), 2) + pow((midLocCircle.y - testY), 2));

  if (distance <= radius) return true;
  else return false; 
}



