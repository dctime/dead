#pragma once

#include "DEAD_bullet.h"
#include <memory>
#include <set>

class DEAD_BulletDirector {
public:
  DEAD_BulletDirector(DEAD_Game* game);
  void registerBullet(DEAD_Bullet* bullet);
  ~DEAD_BulletDirector();
  int bulletCount();
  std::set<DEAD_Bullet*> getBullets();
  void tickBullets();
private:
  bool removeACollisionBullet();
  std::set<DEAD_Bullet*> bullets; 
  DEAD_Game* game;
};
