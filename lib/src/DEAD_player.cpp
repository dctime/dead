#include <DEAD_player.h>

DEAD_Player::DEAD_Player(DEAD_Player::Position* pos)
: speed(3), position(pos) {
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
