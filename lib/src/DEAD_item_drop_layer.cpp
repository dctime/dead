#include <DEAD_item_drop_layer.h>
#include <iostream>

DEAD_ItemDropLayer::DEAD_ItemDropLayer() {
  this->itemDrops.size();

  std::cout << "itemDropLayer Created" << std::endl;
}

std::set<std::shared_ptr<DEAD_ItemDrop>> DEAD_ItemDropLayer::getItemDrops() {
  return this->itemDrops;
}

void DEAD_ItemDropLayer::drop(std::shared_ptr<DEAD_ItemDrop> itemDrop) {
  this->itemDrops.insert(itemDrop);
}

int DEAD_ItemDropLayer::getDropsCount() {
  return this->itemDrops.size();
}
