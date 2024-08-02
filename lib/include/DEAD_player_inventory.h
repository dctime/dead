#pragma once
#include "DEAD_item.h"
#include <cstdint>
#include <memory>

class DEAD_PlayerInventory {
public:
  DEAD_PlayerInventory(DEAD_Player* player);
  const std::vector<std::shared_ptr<DEAD_Item>>& getHotbar();
  DEAD_Item* getHoldItem();
  void dropHoldItem();
  void replaceHoldItem(std::shared_ptr<DEAD_Item> item);
  uint8_t getHotbarIndex();
  void nextItemHotbar();
  void previousItemHotbar();
  void switchItemHotbar(uint8_t index);
private:
  std::vector<std::shared_ptr<DEAD_Item>> hotbar;
  uint8_t hotbarIndex;
  DEAD_Player* player; 
  const int INVENTORY_SIZE;
};
