#pragma once

#include <memory>
#include "DEAD_item.h"
#include "DEAD_weapon.h"
#include "DEAD_map.h"
#include "hitbox/DEAD_circle_hitbox.h"
#include "DEAD_entity.h"
class DEAD_Game;

class DEAD_Player : public DEAD_Entity {
public:
  DEAD_Player();
  ~DEAD_Player();
  SDL_Rect getPlayerTextureRect();
  void pickupOrDrop();
  void summonPistol();
protected:
  void attack();
private:
  void pickupWeapon();
  void dropWeapon(); 
  
  
};
