#pragma once
#include "DEAD_map_object_base.h"
#include "../DEAD_map.h"

class DEAD_CursedDirt : public DEAD_MapObjectBase {
public:
  DEAD_CursedDirt(DEAD_Map::MapLocation loc);
  char getChar() override;
  SDL_Rect getTextureRect() override;
  bool isPlayerCollidable() override;
  bool isZombieCollidable() override;
};
