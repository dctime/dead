#pragma once

#include "DEAD_weapon.h"
#include "DEAD_map.h"
#include "hitbox/DEAD_circle_hitbox.h"
#include <memory>

class DEAD_Game;

class DEAD_Entity :
  public std::enable_shared_from_this<DEAD_Entity> {
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
  void setGame(std::shared_ptr<DEAD_Game> game);
  std::shared_ptr<DEAD_Game> getGame();
  double getSize();
  double getPickItemRadius();
  std::shared_ptr<DEAD_CircleHitbox> getHitbox();
protected:
  virtual void attack() = 0;
  std::shared_ptr<DEAD_Item> holdItem;
  
private:
  DEAD_Map::MapLocation position;
  int speed;
  double rotation;
  std::shared_ptr<DEAD_Game> game;
  double size;
  std::shared_ptr<DEAD_CircleHitbox> hitbox;
};
