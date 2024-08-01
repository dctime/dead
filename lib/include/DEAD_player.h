#pragma once

#include "DEAD_entity.h"
#include "DEAD_item.h"
#include "DEAD_map.h"
#include "DEAD_weapon.h"
#include "hitbox/DEAD_circle_hitbox.h"
#include <memory>
class DEAD_Game;

class DEAD_Player : public DEAD_Entity {
public:
  DEAD_Player(DEAD_Game* game);
  ~DEAD_Player();
  SDL_Rect getTextureRect() override;
  template <typename T> void summonWeapon() {
    this->holdItem = std::make_shared<T>(this);
  }

  void setGame(DEAD_Game* game) override = 0;
  void move(double x, double y) override;

protected:
  void attack();
  void reloadGun();
  void useItem();
  void pickupOrDrop();

private:
  void pickupWeapon();
  void dropWeapon();
};
