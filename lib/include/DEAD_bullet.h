#pragma once

#include "DEAD_player.h"
#include <SDL2/SDL.h>
#include <memory>

class DEAD_Bullet : std::enable_shared_from_this<DEAD_Bullet> {
public:
  DEAD_Bullet(DEAD_Player* owner);
  virtual SDL_Rect getBulletTextureRect() = 0;
  DEAD_Player* getOwner();
  virtual double getBulletSize() = 0;
  DEAD_Map::MapLocation getMapLocation();
  virtual void registerBullet() = 0;
  virtual ~DEAD_Bullet();
private:
  DEAD_Player* owner;
  DEAD_Map::MapLocation pos;
};
