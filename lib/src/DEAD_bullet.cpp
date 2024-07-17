#include "DEAD_bullet.h"
#include <DEAD_game.h>
#include <SDL2/SDL_log.h>
#include <cmath>

DEAD_Bullet::DEAD_Bullet(DEAD_Player* owner, DEAD_Gun* gun, double speed)
: owner(owner), gun(gun), rotation(owner->getRotation()), speed(speed) {
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

double DEAD_Bullet::getRotation() { return this->rotation; }
DEAD_Map::MapLocation DEAD_Bullet::getLoc() { return this->pos; }

void DEAD_Bullet::setLoc(DEAD_Map::MapLocation loc) { this->pos = loc; }
void DEAD_Bullet::move(double x, double y) {
  
  this->pos.x += x;
  this->pos.y += y;
}

void DEAD_Bullet::tickFly() {
  this->move(this->speed * cos(this->rotation * ((M_PI) / 180.0)), this->speed * sin(this->rotation * (M_PI / 180.0)));
}





