#pragma once

class DEAD_Player {
public:
  struct Position {
    double x;
    double y;
  };
  DEAD_Player(DEAD_Player::Position *pos);
  ~DEAD_Player();
  Position *getPos();

private:
  Position *position;
};