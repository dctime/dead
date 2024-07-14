#include <DEAD_game.h>
#include <SDL2/SDL_log.h>
#include <cmath>

DEAD_Bullet::DEAD_Bullet(DEAD_Player* owner, DEAD_Gun* gun)
: owner(owner), gun(gun) {
  double rad = owner->getRotation() * (M_PI / (180.0));
  double bulletX = (owner->getPos())->x + cos(rad) * gun->getBarrelLength();
  double bulletY = (owner->getPos())->y + sin(rad) * gun->getBarrelLength();
  this->pos.x = bulletX;
  this->pos.y = bulletY;
  SDL_Log("[Bullet] init a bullet");
}

DEAD_Player* DEAD_Bullet::getOwner() {
  return this->owner;
}

DEAD_Bullet::~DEAD_Bullet() {}
DEAD_Map::MapLocation DEAD_Bullet::getMapLocation() {
  return this->pos;
}

DEAD_Gun* DEAD_Bullet::getGun() {
  return this->gun; 
}

