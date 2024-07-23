#include "hitbox/DEAD_circle_hitbox.h"
#include <bullets/DEAD_bullet.h>
#include <DEAD_game.h>
#include <SDL2/SDL_log.h>
#include <cmath>
#include <memory>

DEAD_Bullet::DEAD_Bullet(std::shared_ptr<DEAD_Player> owner, std::shared_ptr<DEAD_Gun> gun, double speed, int damage)
: owner(owner), gun(gun), rotation(owner->getRotation()), speed(speed*100), damage(damage) {
  double rad = owner->getRotation() * (M_PI / (180.0));
  double bulletX = (owner->getPos()).x + cos(rad) * gun->getBarrelLength();
  double bulletY = (owner->getPos()).y + sin(rad) * gun->getBarrelLength();
  this->pos.x = bulletX;
  this->pos.y = bulletY;
  SDL_Log("[Bullet] init a bullet");
}

std::shared_ptr<DEAD_Player> DEAD_Bullet::getOwner() {
  return this->owner;
}

DEAD_Bullet::~DEAD_Bullet() {}
int DEAD_Bullet::getDamage() {
  return this->damage;
}
DEAD_Map::MapLocation DEAD_Bullet::getMapLocation() {
  return this->pos;
}

std::shared_ptr<DEAD_Gun> DEAD_Bullet::getGun() {
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

std::shared_ptr<DEAD_CircleHitbox> DEAD_Bullet::getHitBox() {
  std::shared_ptr<DEAD_CircleHitbox> hitbox = std::make_shared<DEAD_CircleHitbox>(this->getBulletSize()/2.0, this->getLoc());
  return hitbox;
}





