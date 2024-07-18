#include <memory>
#include <set>
#include "DEAD_item_drop.h"
class DEAD_ItemDropLayer {
public:
  DEAD_ItemDropLayer();
  std::set<std::shared_ptr<DEAD_ItemDrop>> getItemDrops(); 
  void drop(std::shared_ptr<DEAD_ItemDrop> itemDrop);
  int getDropsCount();
  void getNearItemDrop(DEAD_Map::MapLocation loc, double radius, std::shared_ptr<DEAD_Item>& returnItem);


private:
  std::set<std::shared_ptr<DEAD_ItemDrop>> itemDrops;

  
};
