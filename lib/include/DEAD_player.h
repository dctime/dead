#pragma once

#include "DEAD_entity.h"
#include "items/DEAD_item.h"
#include "DEAD_map.h"
#include "items/weapons/DEAD_weapon.h"
#include "hitbox/DEAD_circle_hitbox.h"
#include "DEAD_player_inventory.h"
#include "decorations/DEAD_decoration_base.h"
#include <memory>
class DEAD_Game;

class DEAD_Player : public DEAD_Entity {
public:
  DEAD_Player(DEAD_Game* game);
  ~DEAD_Player();
  SDL_Rect getTextureRect() override;

  template <typename T> void summonWeapon() {
    inventory->replaceHoldItem(std::make_shared<T>(this));
  }

  void setGame(DEAD_Game* game) override = 0;
  void move(double x, double y) override;
  void setHoldItem(std::shared_ptr<DEAD_Item> item);
  DEAD_PlayerInventory* getInventory();
  void incrementZombieKillCount();
  int getZombieKillCount();
  DEAD_DecorationBase* getCurrentDestoryingDeco();

protected:
  void attack();
  void reloadGun();
  void useItem();
  void pickupOrDrop();
  void interactWithDecoration(int pressTimeIntervalTicks);
  std::unique_ptr<DEAD_PlayerInventory> inventory;

private:
  void pickupItem();
  void dropHoldItem();
  DEAD_DecorationBase* getDecorationInFrontof(double range, double precision);
  int zombieKillcount;
  DEAD_DecorationBase* currentDestroyingDeco;
};
