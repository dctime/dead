#include <DEAD_normal_bullet.h>
#include <DEAD_game.h>
DEAD_NormalBullet::DEAD_NormalBullet(DEAD_Player* owner) : DEAD_Bullet(owner) {
  this->registerBullet();
}

SDL_Rect DEAD_NormalBullet::getBulletTextureRect() {
  SDL_Rect rect = {.x=0, .y=0, .w=100, .h=100};
  return rect;
} 

void DEAD_NormalBullet::registerBullet() {
  this->getOwner()->getGame()->getBulletDirector()->registerBullet(this);
}

