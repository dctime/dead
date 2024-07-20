#pragma once

#include "bullets/DEAD_bullet.h"
#include <memory>
#include <set>

class DEAD_BulletDirector {
public:
  DEAD_BulletDirector(std::shared_ptr<DEAD_Game> game);
  void registerBullet(std::shared_ptr<DEAD_Bullet> bullet);
  ~DEAD_BulletDirector();
  int bulletCount();
  std::set<std::shared_ptr<DEAD_Bullet>> getBullets();
  void tickBullets();
  void checkAndDeleteCollisionBullets();
private:
  void getCollisionBullets(std::vector<std::shared_ptr<DEAD_Bullet>>& bullets);
  std::set<std::shared_ptr<DEAD_Bullet>> bullets; 
  std::shared_ptr<DEAD_Game> game;
};
