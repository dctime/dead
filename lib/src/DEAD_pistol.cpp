#include <DEAD_game.h>
#include <DEAD_pistol.h>
#include <DEAD_normal_bullet.h>
#include <SDL2/SDL_log.h>
#include <iostream>
#include <memory>

DEAD_Pistol::DEAD_Pistol(DEAD_Player* player)
: DEAD_Gun(player) {}

SDL_Rect DEAD_Pistol::getTextureRect() {
  SDL_Rect rect = {.x=100, .y=0, .w=100, .h=100};
  return rect;
}

void DEAD_Pistol::attack() {
  DEAD_Bullet* bullet = new DEAD_NormalBullet(this->getPlayer());
  std::cout << this->getPlayer()->getGame()->getBulletDirector()->bulletCount() << std::endl;
}
