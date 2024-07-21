#pragma once
#include "../DEAD_map.h"
#include "../hitbox/DEAD_rect_hitbox.h"
#include <SDL2/SDL_rect.h>
#include <memory>

class DEAD_MapObjectBase {
public:
  DEAD_MapObjectBase(DEAD_Map::MapLocation loc);
  ~DEAD_MapObjectBase();
  virtual char getChar() = 0;
  std::shared_ptr<DEAD_RectHitbox> getHitBox();
  DEAD_Map::MapLocation getLeftUpLoc();
  virtual bool isPlayerCollidable() = 0;
  virtual bool isZombieCollidable() = 0;
  // TODO: Implement this function to every child
  virtual SDL_Rect getTextureRect();
private:
  DEAD_Map::MapLocation leftUpLoc;
  std::shared_ptr<DEAD_RectHitbox> hitbox;  
};
