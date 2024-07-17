#pragma once

#include "DEAD_weapon.h"
#include "DEAD_map.h"
#include "hitbox/DEAD_circle_hitbox.h"

class DEAD_Game;

class DEAD_Entity {
public:
  DEAD_Entity();
  ~DEAD_Entity();
  DEAD_Map::MapLocation getPos();
  void move(double x, double y);
  void setPos(double x, double y);
  void setSpeed(int speed);
  int getSpeed();
  double getRotation();
  void setRotation(double degree);
  void setGame(DEAD_Game* game);
  DEAD_Game* getGame();
  double getSize();
  DEAD_CircleHitbox* getHitbox();
protected:
  virtual void attack() = 0;

private:
  DEAD_Map::MapLocation position;
  int speed;
  double rotation;
  DEAD_Game* game;
  double size;
  DEAD_CircleHitbox* hitbox;
};