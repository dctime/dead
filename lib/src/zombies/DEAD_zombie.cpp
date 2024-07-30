#include <DEAD_player.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <memory>
#include <zombies/DEAD_zombie.h>

DEAD_Zombie::DEAD_Zombie(DEAD_Game* game)
    : DEAD_Entity::DEAD_Entity(game, 100, 0.8), lastTimeAttackTicks(0),
      attackCoolDown(1000) {
  this->movingUnitVector = {.vectorX=0, .vectorY=0};
  std::cout << "Zombie Built" << std::endl;
}

SDL_Rect DEAD_Zombie::getTextureRect() {
  SDL_Rect rect = {.x = 0, .y = 0, .w = 100, .h = 100};
  return rect;
};

int DEAD_Zombie::getAttackDamage() { return 25; }

bool DEAD_Zombie::attackReady() {
  if (this->lastTimeAttackTicks + attackCoolDown <= SDL_GetTicks64()) {
    return true;
  } else {
    return false;
  }
}

void DEAD_Zombie::bite(DEAD_Player* player) {
  if (!this->getHitbox()->iscollideWithCircle(player->getHitbox()))
    return;
  if (!this->attackReady())
    return;
  player->damage(this->getAttackDamage());
  this->lastTimeAttackTicks = SDL_GetTicks64();
  std::cout << "Player health left: " << player->getHealth() << std::endl;

}

ZombieVector DEAD_Zombie::getMovingUnitVector() {
  return this->movingUnitVector;
}

void DEAD_Zombie::setMovingUnitVector(ZombieVector vector) {
  this->movingUnitVector = vector; 
}






