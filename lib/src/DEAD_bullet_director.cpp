#include "zombies/DEAD_zombie.h"
#include <DEAD_bullet_director.h>
#include <DEAD_game.h>
#include <SDL2/SDL_log.h>
#include <bullets/DEAD_bullet.h>
#include <iostream>
#include <memory>
#include <set>

DEAD_BulletDirector::DEAD_BulletDirector(std::shared_ptr<DEAD_Game> game)
    : game(game) {}

void DEAD_BulletDirector::registerBullet(std::shared_ptr<DEAD_Bullet> bullet) {
  this->bullets.insert(bullet);
  SDL_Log("[Bullet Director] register a bullet");
}

int DEAD_BulletDirector::bulletCount() { return this->bullets.size(); }

DEAD_BulletDirector::~DEAD_BulletDirector() { this->bullets.clear(); }

std::set<std::shared_ptr<DEAD_Bullet>> DEAD_BulletDirector::getBullets() {
  return this->bullets;
}

void DEAD_BulletDirector::tickBullets() {
  for (std::shared_ptr<DEAD_Bullet> bullet : this->bullets) {
    bullet->tickBullet();
  }
}

void DEAD_BulletDirector::checkAndDeleteCollisionBullets() {
  std::vector<std::shared_ptr<DEAD_Bullet>> removingBullets;
  this->getCollisionBullets(removingBullets);
  for (int i = 0; i < removingBullets.size(); i++) {
    this->bullets.erase(removingBullets.at(i));
  }
}

void DEAD_BulletDirector::getCollisionBullets(
    std::vector<std::shared_ptr<DEAD_Bullet>> &bullets) {

  for (std::shared_ptr<DEAD_Bullet> bullet : this->bullets) {
    if (this->game->getCollisionDirector()
            ->bulletCheckCollision(bullet)
            .size() != 0) {
      bullets.push_back(bullet);
      continue;
    }

    std::shared_ptr<DEAD_Zombie> zombie =
        this->game->getCollisionDirector()->bulletCheckCollideZombie(bullet);
    if (zombie == nullptr)
      continue;

    zombie->damage(bullet->getDamage());
    bullets.push_back(bullet);
    if (zombie->getHealth() <= 0) {
      this->game->getZombieDirector()->killZombie(zombie);
    }
  }
}
