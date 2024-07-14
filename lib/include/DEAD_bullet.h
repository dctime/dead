#pragma once

#include "DEAD_player.h"
#include "DEAD_gun.h"
#include <SDL2/SDL.h>
#include <memory>

class DEAD_Bullet {
public:
  DEAD_Bullet(DEAD_Player* owner, DEAD_Gun* gun, double speed);
  virtual SDL_Rect getBulletTextureRect() = 0;
  DEAD_Player* getOwner();
  virtual double getBulletSize() = 0;
  DEAD_Map::MapLocation getMapLocation();
  DEAD_Gun* getGun();
  double getRotation();
  DEAD_Map::MapLocation getLoc();
  void setLoc(DEAD_Map::MapLocation loc);
  void move(double x, double y);
  void tickFly();
  virtual void registerBullet() = 0;
  virtual void tickBullet() = 0;
  virtual ~DEAD_Bullet();
private:
  DEAD_Player* owner;
  DEAD_Map::MapLocation pos;
  DEAD_Gun* gun;
  double rotation;
  double speed;
};
