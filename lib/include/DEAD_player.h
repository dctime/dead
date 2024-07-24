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
  DEAD_Player(std::shared_ptr<DEAD_Game> game);
  ~DEAD_Player();
  SDL_Rect getTextureRect() override;
  void pickupOrDrop();
  void summonPistol();
  void setGame(std::shared_ptr<DEAD_Game> game) override = 0;
  void move(double x, double y) override;
  void reloadGun();
protected:
  void attack();
private:
  void pickupWeapon();
  void dropWeapon(); 
  
  
};
