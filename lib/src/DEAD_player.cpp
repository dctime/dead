#include <DEAD_player.h>
#include <SDL2/SDL_log.h>
#include <iostream>
#include <memory>
#include <ostream>

DEAD_Player::DEAD_Player(DEAD_Player::Position* pos)
: speed(3), position(pos), weapon(nullptr){
}

DEAD_Player::~DEAD_Player() {}

DEAD_Player::Position* DEAD_Player::getPos() {
  return this->position;
}

void DEAD_Player::setPos(double x, double y) {
  this->position->x = x;
  this->position->y = y;
}

void DEAD_Player::setSpeed(int speed) {
  this->speed = speed;
}

int DEAD_Player::getSpeed() {
  return this->speed;
}

void DEAD_Player::pickupWeapon(std::shared_ptr<DEAD_Weapon> weapon) {
  if (this->weapon != nullptr) {
    SDL_Log("[Player] Cant pickup weapon, must have empty hands");
  }
  this->weapon = weapon;
}
