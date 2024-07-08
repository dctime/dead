#include <DEAD_player.h>

DEAD_Player::DEAD_Player(DEAD_Player::Position* pos) {
  this->position = pos;
}

DEAD_Player::~DEAD_Player() {}

DEAD_Player::Position* DEAD_Player::getPos() {
  return this->position;
}
