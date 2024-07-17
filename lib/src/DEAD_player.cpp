#include <DEAD_weapon.h>
#include <DEAD_game.h>
#include <DEAD_player.h>
#include <SDL2/SDL_log.h>
#include <memory>

DEAD_Player::DEAD_Player()
  : DEAD_Entity::DEAD_Entity(), weapon(nullptr) {
  
}

DEAD_Player::~DEAD_Player() {}


void DEAD_Player::pickupWeapon(std::shared_ptr<DEAD_Weapon> weapon) {
  if (this->weapon != nullptr) {
    SDL_Log("[Player] Cant pickup weapon, must have empty hands");
  }
  this->weapon = weapon;
}

SDL_Rect DEAD_Player::getPlayerTextureRect() {
  if (this->weapon == nullptr) {
    SDL_Rect rect = {.x=0, .y=0, .w=100, .h=100};
    return rect;
  }

  return this->weapon->getTextureRect();
}

void DEAD_Player::attack() {
  if (weapon == nullptr) {
    return;
  }
  this->weapon->attack();
}



