#include "DEAD_bullet.h"
#include <DEAD_bullet_director.h>
#include <DEAD_game.h>
#include <SDL2/SDL_log.h>
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
  std::set<DEAD_Bullet *> tempRemoveBullet;
  for (DEAD_Bullet *bullet : this->bullets) {
    if (this->game->getCollisionDirector()
            ->bulletCheckCollision(bullet)
            .size() != 0) {
      tempRemoveBullet.insert(bullet);
    } else {
      bullet->tickBullet();
    }
  }

  for (DEAD_Bullet* removingBullet : tempRemoveBullet) {
    this->bullets.erase(removingBullet);
    delete removingBullet;
  }
}
