#include <DEAD_game.h>
#include <DEAD_player.h>
#include <DEAD_weapon.h>
#include <guns/DEAD_pistol.h>
#include <SDL2/SDL_log.h>
#include <memory>

DEAD_Player::DEAD_Player() : DEAD_Entity::DEAD_Entity(), weapon(nullptr) {}

DEAD_Player::~DEAD_Player() {}

void DEAD_Player::pickupOrDrop() {
  if (this->weapon != nullptr) {
    this->dropWeapon();
  } else {
    this->pickupWeapon();
  }

}
void DEAD_Player::dropWeapon() {
  this->getGame()->getItemDropLayer()->drop(this->weapon->getItemDrop());
  this->weapon = nullptr;
  SDL_Log("Dropped Weapons Count: %d", this->getGame()->getItemDropLayer()->getDropsCount()); 
}

void DEAD_Player::pickupWeapon() {
  std::shared_ptr<DEAD_Weapon> weapon = std::make_shared<DEAD_Pistol>(this);
  this->weapon = weapon;
  SDL_Log("Picked Up Weapon");
}

SDL_Rect DEAD_Player::getPlayerTextureRect() {
  if (this->weapon == nullptr) {
    SDL_Rect rect = {.x = 0, .y = 0, .w = 100, .h = 100};
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
