#pragma once
#include "DEAD_item_drop.h"
#include <memory>

class DEAD_Item {
public:
  DEAD_Item();
  virtual ~DEAD_Item();
  virtual std::shared_ptr<DEAD_ItemDrop> getItemDrop() = 0;
protected:
  std::shared_ptr<DEAD_ItemDrop> itemDrop;
};
