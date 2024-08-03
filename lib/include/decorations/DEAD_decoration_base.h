#pragma once
#include <SDL2/SDL_rect.h>
#include <memory>
#include "../DEAD_map.h"
#include "../hitbox/DEAD_circle_hitbox.h"

class DEAD_ControllablePlayer;

class DEAD_DecorationBase {
public:
  DEAD_DecorationBase(DEAD_Map::MapLocation loc, double width, double height, double rotationAngle, double interactRadius);
  virtual SDL_Rect getTextureRect() = 0;
  DEAD_Map::MapLocation getLoc();
  double getWidth();
  double getHeight();
  double getRotationAngle();
  DEAD_CircleHitbox* getInteractHitbox();
  virtual double destroyRequireTicks() = 0;
  // returns true when deco is destroyed
  bool destroying(int ticksInterval, DEAD_ControllablePlayer* player);
  double getDestroyPercentage();
private:
  DEAD_Map::MapLocation loc;
  double width;
  double height;
  double rotationAngle;
  std::unique_ptr<DEAD_CircleHitbox> interactHitbox;
  void destroy();

  // Only work properly when player is breaking it
  double destroyPercentage;
  
};
