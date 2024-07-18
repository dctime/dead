#include <bullets/DEAD_bullet.h>
#include <DEAD_bullet_director.h>
#include <DEAD_game.h>
#include <SDL2/SDL_log.h>
#include <iostream>
#include <set>

DEAD_BulletDirector::DEAD_BulletDirector(DEAD_Game *game) : game(game) {}

void DEAD_BulletDirector::registerBullet(DEAD_Bullet *bullet) {
  this->bullets.insert(bullet);
  SDL_Log("[Bullet Director] register a bullet");
}

int DEAD_BulletDirector::bulletCount() { return this->bullets.size(); }

DEAD_BulletDirector::~DEAD_BulletDirector() {
  for (DEAD_Bullet *bullet : this->bullets) {
    delete bullet;
  }
  this->bullets.clear();
}

std::set<DEAD_Bullet *> DEAD_BulletDirector::getBullets() {
  return this->bullets;
}

void DEAD_BulletDirector::tickBullets() {
  
  std::vector<DEAD_Bullet *> removingBullets;
  this->getCollisionBullets(removingBullets);
  for (int i = 0; i < removingBullets.size(); i++) {
    this->bullets.erase(removingBullets.at(i));
  }

  for (DEAD_Bullet *bullet : this->bullets) {
    bullet->tickBullet();
  }
}

void DEAD_BulletDirector::getCollisionBullets(
    std::vector<DEAD_Bullet *> &bullets) {

  for (DEAD_Bullet *bullet : this->bullets) {
    if (this->game->getCollisionDirector()
            ->bulletCheckCollision(bullet)
            .size() != 0) {
      bullets.push_back(bullet);
    }
  }
}
