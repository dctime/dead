#pragma once
#include <SDL2/SDL_rect.h>
#include "../DEAD_map.h"

class DEAD_DecorationBase {
public:
  DEAD_DecorationBase(DEAD_Map::MapLocation loc, double width, double height);
  virtual SDL_Rect getTextureRect() = 0;
  DEAD_Map::MapLocation getLoc();
  double getWidth();
  double getHeight();
private:
  DEAD_Map::MapLocation loc;
  double width;
  double height;

};
