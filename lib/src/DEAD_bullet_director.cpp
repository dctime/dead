#include "zombies/DEAD_zombie.h"
#include <DEAD_bullet_director.h>
#include <DEAD_game.h>
#include <SDL2/SDL_log.h>
#include <algorithm>
#include <bullets/DEAD_bullet.h>
#include <iostream>
#include <memory>
#include <set>

DEAD_BulletDirector::DEAD_BulletDirector(DEAD_Game* game)
    : game(game) {}

void DEAD_BulletDirector::registerBullet(std::unique_ptr<DEAD_Bullet>& bullet) {
  this->bullets.insert(std::move(bullet));
  SDL_Log("[Bullet Director] register a bullet");
}

int DEAD_BulletDirector::bulletCount() { return this->bullets.size(); }

DEAD_BulletDirector::~DEAD_BulletDirector() { this->bullets.clear(); }

std::set<std::unique_ptr<DEAD_Bullet>>& DEAD_BulletDirector::getBullets() {
  return this->bullets;
}

void DEAD_BulletDirector::tickBullets() {
  for (const std::unique_ptr<DEAD_Bullet>& bullet : this->bullets) {
    bullet->tickBullet();
  }
}

void DEAD_BulletDirector::checkAndDeleteCollisionBullets() {
  std::vector<DEAD_Bullet*> removingBullets;
  this->getCollisionBullets(removingBullets);
  for (int i = 0; i < removingBullets.size(); i++) {
    
    this->deleteBullet(removingBullets.at(i));
  }
}

void DEAD_BulletDirector::deleteBullet(DEAD_Bullet* bullet) {
  for (const std::unique_ptr<DEAD_Bullet>& bulletUnique : this->bullets) {
    if (bulletUnique.get() != bullet) continue;
    this->bullets.erase(bulletUnique);
    break;
  }
}

void DEAD_BulletDirector::getCollisionBullets(
    std::vector<DEAD_Bullet*>& bullets) {

  for (const std::unique_ptr<DEAD_Bullet>& bullet : this->bullets) {
    if (this->game->getCollisionDirector()
            ->bulletCheckCollision(bullet.get())
            .size() != 0) {
      bullets.push_back(bullet.get());
      continue;
    }

    DEAD_Zombie* zombie =
        this->game->getCollisionDirector()->bulletCheckCollideZombie(bullet.get());
    if (zombie == nullptr)
      continue;

    this->game->getSoundDirector()->playHitWithBullet();
    zombie->damage(bullet->getDamage(), bullet->getOwner());

    

    bullets.push_back(bullet.get());
    
  }
}
