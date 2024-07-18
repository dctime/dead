#include <memory>
#include <set>
#include "DEAD_item_drop.h"
class DEAD_ItemDropLayer {
public:
  std::set<std::shared_ptr<DEAD_ItemDrop>> getItemDrops(); 
  void drop(std::shared_ptr<DEAD_ItemDrop> itemDrop);
  int getDropsCount();
private:
  std::set<std::shared_ptr<DEAD_ItemDrop>> itemDrops;

  
};
