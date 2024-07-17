#pragma once

#include <memory>
#include "DEAD_weapon.h"
#include "DEAD_map.h"
#include "hitbox/DEAD_circle_hitbox.h"
#include "DEAD_entity.h"
class DEAD_Game;

class DEAD_Player : public DEAD_Entity {
public:
  DEAD_Player();
  ~DEAD_Player();
  
  void pickupWeapon(std::shared_ptr<DEAD_Weapon> weapon);
  SDL_Rect getPlayerTextureRect();
protected:
  void attack() override;
private:
  
  std::shared_ptr<DEAD_Weapon> weapon;
  
};
