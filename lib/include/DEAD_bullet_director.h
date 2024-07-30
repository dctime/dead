#pragma once

#include "bullets/DEAD_bullet.h"
#include <memory>
#include <set>

class DEAD_BulletDirector {
public:
  DEAD_BulletDirector(DEAD_Game* game);
  void registerBullet(std::unique_ptr<DEAD_Bullet>& bullet);
  ~DEAD_BulletDirector();
  int bulletCount();
  std::set<std::unique_ptr<DEAD_Bullet>>& getBullets();
  void tickBullets();
  void checkAndDeleteCollisionBullets();
  void deleteBullet(DEAD_Bullet* bullet);
private:
  void getCollisionBullets(std::vector<DEAD_Bullet*>& bullets);
  std::set<std::unique_ptr<DEAD_Bullet>> bullets; 
  DEAD_Game* game;
};
