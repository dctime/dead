#pragma once
#include "../DEAD_map.h"


class DEAD_MapObjectBase {
public:
  DEAD_MapObjectBase(DEAD_Map::MapLocation loc);
  virtual char getChar() = 0;
  DEAD_Map::MapLocation getLeftUpLoc();
private:
  DEAD_Map::MapLocation leftUpLoc;
};
