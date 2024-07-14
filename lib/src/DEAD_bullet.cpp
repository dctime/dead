#include <DEAD_game.h>
#include <SDL2/SDL_log.h>

DEAD_Bullet::DEAD_Bullet(DEAD_Player* owner)
: owner(owner) {
  this->pos = *owner->getPos();
  SDL_Log("[Bullet] init a bullet");
}

DEAD_Player* DEAD_Bullet::getOwner() {
  return this->owner;
}


