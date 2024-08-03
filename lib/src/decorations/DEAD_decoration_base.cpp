#include <decorations/DEAD_decoration_base.h>

DEAD_DecorationBase::DEAD_DecorationBase(DEAD_Map::MapLocation loc, double width, double height, double rotationAngle) 
  : loc(loc), width(width), height(height), rotationAngle(rotationAngle) {
}

DEAD_Map::MapLocation DEAD_DecorationBase::getLoc() {
  return this->loc;
}

double DEAD_DecorationBase::getWidth() {
  return this->width;
}

double DEAD_DecorationBase::getHeight() {
  return this->height;
}

double DEAD_DecorationBase::getRotationAngle() {
  return this->rotationAngle;
}
