#include <memory>
#include "DEAD_decoration_layer.h"

class DEAD_DecorationLayerBuilder {
public:
  DEAD_DecorationLayerBuilder(DEAD_Game* game);
  void build(std::unique_ptr<DEAD_DecorationLayer>& layer);
private:
  DEAD_Game* game;
  std::unique_ptr<DEAD_DecorationLayer> decorationLayer;
  void addPileOfPaperCluster(DEAD_Map::MapLocation loc, double sigma, double maxWidth, double maxHeight, int quantity, int withItemDropQuantity);

};
