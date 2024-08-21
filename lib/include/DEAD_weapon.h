#pragma once

#include "DEAD_item.h"
#include <SDL2/SDL.h>
#include <memory>
#include <string>

class DEAD_Player;

class DEAD_Weapon : public DEAD_Item {
public:
  DEAD_Weapon(DEAD_Player* owner, const int COOLDOWN_TIME);
  virtual ~DEAD_Weapon();
  virtual SDL_Rect getTextureRect() override = 0;
  virtual void attack() = 0;
  virtual SDL_Rect getItemTextureRect() override = 0;
  virtual std::string getName() override = 0;
  virtual std::string getNote() override = 0;
  double checkStillCooling();
  bool use() override { return false; };

private:
  const int COOLDOWN_TIME;
  int startCoolingTicks;


protected:
  void startCoolDown();
};
