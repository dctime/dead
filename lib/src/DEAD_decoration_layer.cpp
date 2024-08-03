#include "decorations/DEAD_decoration_base.h"
#include <DEAD_decoration_layer.h>
#include <memory>

const std::vector<std::unique_ptr<DEAD_DecorationBase>>& DEAD_DecorationLayer::getDecorations() {
  return this->decorations; 
}

DEAD_DecorationBase* DEAD_DecorationLayer::getFirstDecorationByLoc(DEAD_Map::MapLocation loc) {
  for (int index = this->decorations.size()-1; index >= 0; index--) {
    DEAD_DecorationBase* deco = this->decorations.at(index).get();
    if (deco->getInteractHitbox()->pointInHitbox(loc)) return deco;
  }
  return nullptr;
}

void DEAD_DecorationLayer::deleteDeco(DEAD_DecorationBase* deco) {
  for (auto itr = this->decorations.begin(); itr != this->decorations.end(); itr++) {
    if (itr->get() != deco) continue;
    this->decorations.erase(itr);
    break;
  }
}

