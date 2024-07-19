#pragma once
#include "DEAD_item_drop.h"
#include <SDL2/SDL.h>
#include <memory>

class DEAD_Item : public std::enable_shared_from_this<DEAD_Item>{
public:
  DEAD_Item();
  virtual ~DEAD_Item();
  virtual std::shared_ptr<DEAD_ItemDrop> getItemDrop() = 0;
  virtual SDL_Rect getItemTextureRect() = 0;
  void unbindItemDrop();
protected:
  std::shared_ptr<DEAD_ItemDrop> itemDrop;
};
