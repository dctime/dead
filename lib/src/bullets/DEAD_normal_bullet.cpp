#include "bullets/DEAD_bullet.h"
#include <bullets/DEAD_normal_bullet.h>
#include <DEAD_game.h>
#include <memory>
DEAD_NormalBullet::DEAD_NormalBullet(std::shared_ptr<DEAD_Player> owner, std::shared_ptr<DEAD_Gun> gun) 
  : DEAD_Bullet(owner, gun, 0.002) {
  this->registerBullet();
}

SDL_Rect DEAD_NormalBullet::getBulletTextureRect() {
  SDL_Rect rect = {.x=0, .y=0, .w=100, .h=100};
  return rect;
} 

void DEAD_NormalBullet::registerBullet() {
  std::shared_ptr<DEAD_NormalBullet> shared_from_this = std::static_pointer_cast<DEAD_NormalBullet>(DEAD_Bullet::shared_from_this());
  this->getOwner()->getGame()->getBulletDirector()->registerBullet(shared_from_this);
}

double DEAD_NormalBullet::getBulletSize() {
  return 0.3;
}

void DEAD_NormalBullet::tickBullet() {
  this->tickFly();     
}

