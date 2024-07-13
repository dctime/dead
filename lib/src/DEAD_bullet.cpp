#include <DEAD_game.h>

DEAD_Bullet::DEAD_Bullet(DEAD_Player* owner)
: owner(owner) {
  owner->getGame()->getBulletDirector()->registerBullet(this);
  this->pos = *owner->getPos();
}

