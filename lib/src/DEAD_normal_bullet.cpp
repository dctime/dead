#include "DEAD_player.h"
#include <DEAD_normal_bullet.h>

DEAD_NormalBullet::DEAD_NormalBullet(DEAD_Player* owner) : DEAD_Bullet(owner) {}
DEAD_NormalBullet::~DEAD_NormalBullet() {}

SDL_Rect DEAD_NormalBullet::getBulletTextureRect() {
  SDL_Rect rect = {.x=0, .y=0, .w=100, .h=100};
  return rect;
}
