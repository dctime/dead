#pragma once
#include "DEAD_item_drop.h"
#include <SDL2/SDL.h>
#include <memory>

class DEAD_Player;

class DEAD_Item : public std::enable_shared_from_this<DEAD_Item>{
public:
  DEAD_Item(DEAD_Player* owner);
  virtual ~DEAD_Item();
  virtual std::shared_ptr<DEAD_ItemDrop> getItemDrop();
  virtual std::shared_ptr<DEAD_ItemDrop> getItemDrop(double x, double y);
  virtual SDL_Rect getTextureRect() = 0;
  virtual SDL_Rect getItemTextureRect() = 0;
  void unbindItemDrop();
  DEAD_Player* getPlayer();
  void setPlayer(DEAD_Player* player); 
  virtual void use() = 0;
protected:
  std::shared_ptr<DEAD_ItemDrop> itemDrop;
private:
  DEAD_Player* owner;
};
