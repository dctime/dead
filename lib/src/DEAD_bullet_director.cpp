#include "DEAD_bullet.h"
#include <DEAD_bullet_director.h>
#include <SDL2/SDL_log.h>
#include <DEAD_game.h>
#include <iostream>
#include <set>

DEAD_BulletDirector::DEAD_BulletDirector(DEAD_Game* game) 
  : game(game) {
}

void DEAD_BulletDirector::registerBullet(DEAD_Bullet* bullet) {
  this->bullets.insert(bullet);
  SDL_Log("[Bullet Director] register a bullet");
}

int DEAD_BulletDirector::bulletCount() {
  return this->bullets.size();
}

DEAD_BulletDirector::~DEAD_BulletDirector() {
  for (DEAD_Bullet* bullet : this->bullets) {
    delete bullet;
  }
  this->bullets.clear();
}

std::set<DEAD_Bullet*> DEAD_BulletDirector::getBullets() {
  return this->bullets;
}

void DEAD_BulletDirector::tickBullets() {
  while (this->removeACollisionBullet()) {
    std::cout << "Removing A Collision Bullet" << std::endl;
  }

  for (DEAD_Bullet* bullet : this->bullets) {
    bullet->tickBullet();
  }
}

bool DEAD_BulletDirector::removeACollisionBullet() {
  bool hasCollision = false;
  DEAD_Bullet* collisionBullet = nullptr;
  

  for (DEAD_Bullet* bullet : this->bullets) {
    if (this->game->getCollisionDirector()->bulletCheckCollision(bullet).size() != 0) {
      collisionBullet = bullet;
      hasCollision = true;
    }

    if (hasCollision) break;
  }

  if (hasCollision) {
    std::cout << "Delete items: " << collisionBullet << " Erases:"  << this->bullets.erase(collisionBullet) << std::endl;
    delete collisionBullet;
  }

  return hasCollision;
}

