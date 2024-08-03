#pragma once
#include "decorations/DEAD_decoration_base.h"
#include <memory>
#include <set>
class DEAD_DecorationLayer {
public:
  const std::set<std::unique_ptr<DEAD_DecorationBase>>& getDecorations();
private:
  std::set<std::unique_ptr<DEAD_DecorationBase>> decorations;
  friend class DEAD_DecorationLayerBuilder;
};
