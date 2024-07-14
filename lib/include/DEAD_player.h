#pragma once

#include <memory>
#include "DEAD_weapon.h"

class DEAD_Game;

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
  SDL_Rect getPlayerTextureRect();
  double getRotation();
  void setRotation(double degree);
  void setGame(DEAD_Game* game);
  DEAD_Game* getGame();
protected:
  void attack();
private:
  Position *position;
  int speed;
  std::shared_ptr<DEAD_Weapon> weapon;
  double rotation;
  DEAD_Game* game;
};
