#include <DEAD_bullet_director.h>
#include <SDL2/SDL_log.h>

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

