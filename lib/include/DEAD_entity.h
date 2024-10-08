#pragma once

#include "items/weapons/DEAD_weapon.h"
#include "DEAD_map.h"
#include "hitbox/DEAD_circle_hitbox.h"
#include <memory>

class DEAD_Game;

class DEAD_Entity :
  public std::enable_shared_from_this<DEAD_Entity> {
public:
  DEAD_Entity(DEAD_Game* game, int maxHealth, double size);
  ~DEAD_Entity();
  DEAD_Map::MapLocation getPos();
  virtual SDL_Rect getTextureRect() = 0;
  virtual void move(double x, double y);
  void setPos(double x, double y);
  void setSpeed(int speed);
  int getSpeed();
  double getRotation();
  void setRotation(double degree);
  virtual void setGame(DEAD_Game* game);
  DEAD_Game* getGame();
  double getSize();
  double getPickItemRadius();
  DEAD_CircleHitbox* getHitbox();
  int getMaxhealth();
  int getHealth();
  std::shared_ptr<DEAD_Item> getHoldItem();
  void setMaxHealth(int health);
  void setHealth(int health);
  void damage(int health);
  bool checkIfInKnockback();
  bool checkhealthIsDead();
  void setEntityName(std::string name);
  std::string getEntityName();
protected:
  std::shared_ptr<DEAD_Item> holdItem;
  DEAD_Game* game;
private:
  DEAD_Map::MapLocation position;
  int speed;
  double rotation;
  double size;
  std::unique_ptr<DEAD_CircleHitbox> hitbox;
  int health;
  int maxHealth;
  int lastTimeBeenHitTicks;
  int knockBackCooldown;
  std::string entityName;
};
