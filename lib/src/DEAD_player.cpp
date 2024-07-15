#include <DEAD_weapon.h>
#include <DEAD_game.h>
#include <DEAD_player.h>
#include <SDL2/SDL_log.h>
#include <iostream>
#include <memory>

DEAD_Player::DEAD_Player(DEAD_Map::MapLocation* pos)
: speed(3), position(pos), weapon(nullptr), rotation(0){
}

DEAD_Player::~DEAD_Player() {}

DEAD_Map::MapLocation* DEAD_Player::getPos() {
  return this->position;
}

void DEAD_Player::setPos(double x, double y) {
  this->position->x = x;
  this->position->y = y;
}

void DEAD_Player::setSpeed(int speed) {
  this->speed = speed;
}

void DEAD_Player::setRotation(double rotation) {
  this->rotation = rotation;
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

SDL_Rect DEAD_Player::getPlayerTextureRect() {
  if (this->weapon == nullptr) {
    SDL_Rect rect = {.x=0, .y=0, .w=100, .h=100};
    return rect;
  }

  return this->weapon->getTextureRect();
}

double DEAD_Player::getRotation() {
  return this->rotation; 
}

void DEAD_Player::setGame(DEAD_Game* game) {
  this->game = game;
}

DEAD_Game* DEAD_Player::getGame() {
  return this->game;
}

void DEAD_Player::attack() {
  if (weapon == nullptr) {
    return;
  }
  this->weapon->attack();
}

void DEAD_Player::move(double x, double y) {
  this->setPos(this->getPos()->x+x, this->getPos()->y+y);
  this->getGame()->getCollisionDirector()->playerCheckCollision(this);
}






