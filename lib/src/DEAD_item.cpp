#include "DEAD_item_drop.h"
#include <DEAD_item.h>
#include <memory>

DEAD_Item::DEAD_Item()
  : itemDrop(nullptr) {}
DEAD_Item::~DEAD_Item() {}
void DEAD_Item::unbindItemDrop() {
  this->itemDrop = nullptr;
}
