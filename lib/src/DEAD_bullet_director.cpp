#include <DEAD_bullet_director.h>

void DEAD_BulletDirector::registerBullet(DEAD_Bullet* bullet) {
  this->bullets.insert(bullet);
}

