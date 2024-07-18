#pragma once


#include <memory>

class DEAD_Item;

class DEAD_ItemDrop {
public:
  DEAD_ItemDrop(std::shared_ptr<DEAD_Item> item);
  std::shared_ptr<DEAD_Item> getItem();
private:
  std::shared_ptr<DEAD_Item> item;
};
