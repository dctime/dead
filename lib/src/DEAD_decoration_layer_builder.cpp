#include "DEAD_decoration_layer.h"
#include <DEAD_decoration_layer_builder.h>
#include <algorithm>
#include <memory>
#include <decorations/DEAD_pile_of_paper.h>
#include <DEAD_map.h>

DEAD_DecorationLayerBuilder::DEAD_DecorationLayerBuilder()
  : decorationLayer(std::make_unique<DEAD_DecorationLayer>()){
  DEAD_Map::MapLocation loc = {.x=1.5, .y=1.5};
  this->decorationLayer->decorations.insert(std::make_unique<DEAD_PileOfPaper>(loc)); 
}

void DEAD_DecorationLayerBuilder::build(std::unique_ptr<DEAD_DecorationLayer>& layer) {
  layer = std::move(this->decorationLayer);
}
