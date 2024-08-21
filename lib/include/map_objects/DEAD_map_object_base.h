#pragma once
#include "../DEAD_map.h"
#include "../hitbox/DEAD_rect_hitbox.h"
#include <SDL2/SDL_rect.h>
#include <memory>

class DEAD_MapObjectBase {
public:
  DEAD_MapObjectBase(DEAD_Map::MapLocation loc);
  virtual ~DEAD_MapObjectBase();
  virtual char getChar() = 0;
  DEAD_RectHitbox* getHitBox();
  DEAD_Map::MapLocation getLeftUpLoc();
  virtual bool isPlayerCollidable() = 0;
  virtual bool isZombieCollidable() = 0;
  virtual SDL_Rect getTextureRect();
  virtual std::string getName() = 0;
  virtual std::string getNote() = 0;
private:
  DEAD_Map::MapLocation leftUpLoc;
  std::unique_ptr<DEAD_RectHitbox> hitbox;  
};
