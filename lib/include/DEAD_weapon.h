#pragma once

#include <string>
#include <SDL2/SDL.h>
#include "DEAD_item.h"

class DEAD_Player;

class DEAD_Weapon : public DEAD_Item {
public:
  DEAD_Weapon(DEAD_Player* owner);
  virtual ~DEAD_Weapon();
  virtual SDL_Rect getTextureRect() = 0;
  DEAD_Player* getPlayer();
  virtual void attack() = 0;
  virtual std::shared_ptr<DEAD_ItemDrop> getItemDrop() override = 0;
private:
  DEAD_Player* owner;
};
