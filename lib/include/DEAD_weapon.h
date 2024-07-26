#pragma once

#include "DEAD_item.h"
#include <SDL2/SDL.h>
#include <memory>
#include <string>

class DEAD_Player;

class DEAD_Weapon : public DEAD_Item {
public:
  DEAD_Weapon(std::shared_ptr<DEAD_Player> owner, const int COOLDOWN_TIME);
  virtual ~DEAD_Weapon();
  virtual SDL_Rect getTextureRect() override = 0;
  std::shared_ptr<DEAD_Player> getPlayer();
  virtual void attack() = 0;
  virtual std::shared_ptr<DEAD_ItemDrop> getItemDrop() override = 0;
  virtual SDL_Rect getItemTextureRect() override = 0;
  double checkStillCooling();

private:
  std::shared_ptr<DEAD_Player> owner;
  const int COOLDOWN_TIME;
  int startCoolingTicks;


protected:
  void startCoolDown();
};
