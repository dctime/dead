#include <DEAD_decoration_layer.h>
#include <memory>

const std::set<std::unique_ptr<DEAD_DecorationBase>>& DEAD_DecorationLayer::getDecorations() {
  return this->decorations; 
}

