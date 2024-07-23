#pragma once

#include "DEAD_weapon.h"
#include "DEAD_map.h"
#include "hitbox/DEAD_circle_hitbox.h"
#include <memory>

class DEAD_Game;

class DEAD_Entity :
  public std::enable_shared_from_this<DEAD_Entity> {
public:
  DEAD_Entity(std::shared_ptr<DEAD_Game> game, int maxHealth);
  ~DEAD_Entity();
  DEAD_Map::MapLocation getPos();
  virtual SDL_Rect getTextureRect() = 0;
  virtual void move(double x, double y);
  void setPos(double x, double y);
  void setSpeed(int speed);
  int getSpeed();
  double getRotation();
  void setRotation(double degree);
  virtual void setGame(std::shared_ptr<DEAD_Game> game);
  std::shared_ptr<DEAD_Game> getGame();
  double getSize();
  double getPickItemRadius();
  std::shared_ptr<DEAD_CircleHitbox> getHitbox();
  int getMaxhealth();
  int getHealth();
  void setMaxHealth(int health);
  void setHealth(int health);
  void damage(int health);
protected:
  std::shared_ptr<DEAD_Item> holdItem;
  std::shared_ptr<DEAD_Game> game;
private:
  DEAD_Map::MapLocation position;
  int speed;
  double rotation;
  double size;
  std::shared_ptr<DEAD_CircleHitbox> hitbox;
  int health;
  int maxHealth;
};
