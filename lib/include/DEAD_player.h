#pragma once
#include "DEAD_pistol.h"
#include "DEAD_shotgun.h"
#include <memory>

class DEAD_Player {
public:
  struct Position {
    double x;
    double y;
  };
  DEAD_Player(DEAD_Player::Position *pos);
  ~DEAD_Player();
  Position *getPos();
  void setPos(double x, double y);
  void setSpeed(int speed);
  int getSpeed();
  void pickupWeapon(std::shared_ptr<DEAD_Weapon> weapon);
private:
  Position *position;
  int speed;
  std::shared_ptr<DEAD_Weapon> weapon;
};
