#pragma once

#include "DEAD_subrenderer_base.h"
#include <vector>
#include "../labels/DEAD_label_base.h"

class DEAD_LabelRenderer : public DEAD_SubRendererBase {
public:
  DEAD_LabelRenderer(DEAD_Renderer* renderer);
  virtual ~DEAD_LabelRenderer();
  void render() override;
  void addPointLabel(double mapX, double mapY, double radius);
private:
  std::vector<std::unique_ptr<DEAD_LabelBase>> labels;
};
