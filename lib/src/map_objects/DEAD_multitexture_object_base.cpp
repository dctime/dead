#include "map_objects/DEAD_map_object_base.h"
#include <SDL2/SDL_rect.h>
#include <map_objects/DEAD_multitexture_object_base.h>
#include <random>

DEAD_MultitextureObjectBase::DEAD_MultitextureObjectBase(
    DEAD_Map::MapLocation loc)
    : DEAD_MapObjectBase(loc), currentTextureIndex(-1), direction(DEAD_MapObjectDirection::HORIZONTAL) {}

DEAD_MultitextureObjectBase::~DEAD_MultitextureObjectBase() {}

SDL_Rect DEAD_MultitextureObjectBase::getTextureRect() {
  if (currentTextureRects.size() == 0)
    this->currentTextureRects = this->getTextureRects();

  if (currentTextureIndex == -1) {
    std::random_device rd;
    std::uniform_int_distribution<int> dis(0, this->currentTextureRects.size() - 1);
    this->currentTextureIndex = dis(rd);
  }
  return currentTextureRects.at(this->currentTextureIndex);
}

DEAD_MapObjectDirection DEAD_MultitextureObjectBase::getDirection() {
  return this->direction;
}

void DEAD_MultitextureObjectBase::setDirection(DEAD_MapObjectDirection direction) {
  this->direction = direction;
}

void DEAD_MultitextureObjectBase::resetTextureRects() {
  this->currentTextureRects.clear();
  this->currentTextureIndex = -1;
}
