#pragma once
#include "decorations/DEAD_decoration_base.h"
#include <memory>
#include <set>


class DEAD_DecorationLayer {
public:
  const std::vector<std::unique_ptr<DEAD_DecorationBase>>& getDecorations();
  DEAD_DecorationBase* getFirstDecorationByLoc(DEAD_Map::MapLocation loc);
  void deleteDeco(DEAD_DecorationBase* deco);
private:
  std::vector<std::unique_ptr<DEAD_DecorationBase>> decorations;
  friend class DEAD_DecorationLayerBuilder;
};
