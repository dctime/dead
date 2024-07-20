#pragma once


#include <memory>
#include <string>
#include <SDL2/SDL.h>
#include "DEAD_item.h"

class DEAD_Player;

class DEAD_Weapon : public DEAD_Item {
public:
  DEAD_Weapon(std::shared_ptr<DEAD_Player> owner);
  virtual ~DEAD_Weapon();
  virtual SDL_Rect getTextureRect() override = 0;
  std::shared_ptr<DEAD_Player> getPlayer();
  virtual void attack() = 0;
  virtual std::shared_ptr<DEAD_ItemDrop> getItemDrop() override = 0;
  virtual SDL_Rect getItemTextureRect() override = 0;
private:
  std::shared_ptr<DEAD_Player> owner;
};
