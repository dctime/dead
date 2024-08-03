#include <memory>
#include "DEAD_decoration_layer.h"

class DEAD_DecorationLayerBuilder {
public:
  DEAD_DecorationLayerBuilder();
  void build(std::unique_ptr<DEAD_DecorationLayer>& layer);
private:
  std::unique_ptr<DEAD_DecorationLayer> decorationLayer;
};
