#pragma once

#include <memory>
#include "DEAD_weapon.h"
#include "DEAD_map.h"
class DEAD_Game;

class DEAD_Player {
public:
  DEAD_Player(DEAD_Map::MapLocation *pos);
  ~DEAD_Player();
  DEAD_Map::MapLocation *getPos();
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
  DEAD_Map::MapLocation *position;
  int speed;
  std::shared_ptr<DEAD_Weapon> weapon;
  double rotation;
  DEAD_Game* game;
};
