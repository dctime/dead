#include "bullets/DEAD_bullet.h"
#include <bullets/DEAD_normal_bullet.h>
#include <DEAD_game.h>
#include <memory>
DEAD_NormalBullet::DEAD_NormalBullet(DEAD_Player* owner, DEAD_Gun* gun) 
  : DEAD_Bullet(owner, gun, 0.002, 25) {
}

SDL_Rect DEAD_NormalBullet::getBulletTextureRect() {
  SDL_Rect rect = {.x=0, .y=0, .w=100, .h=100};
  return rect;
} 

double DEAD_NormalBullet::getBulletSize() {
  return 0.3;
}

void DEAD_NormalBullet::tickBullet() {
  this->tickFly();     
}

