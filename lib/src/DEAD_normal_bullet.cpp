#include <DEAD_normal_bullet.h>
#include <DEAD_game.h>
DEAD_NormalBullet::DEAD_NormalBullet(DEAD_Player* owner, DEAD_Gun* gun) : DEAD_Bullet(owner, gun, 0.002) {
  this->registerBullet();
}

SDL_Rect DEAD_NormalBullet::getBulletTextureRect() {
  SDL_Rect rect = {.x=0, .y=0, .w=100, .h=100};
  return rect;
} 

void DEAD_NormalBullet::registerBullet() {
  this->getOwner()->getGame()->getBulletDirector()->registerBullet(this);
}

double DEAD_NormalBullet::getBulletSize() {
  return 0.3;
}

void DEAD_NormalBullet::tickBullet() {
  this->tickFly();     
}

