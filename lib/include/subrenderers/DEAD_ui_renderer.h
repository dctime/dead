#pragma once 
#include "../ui/DEAD_ui.h"
#include <memory>
#include <vector>
#include "DEAD_subrenderer_base.h"

class DEAD_UIRenderer : public DEAD_SubRendererBase {
public:
  DEAD_UIRenderer(DEAD_Renderer* renderer);
  void render() override;
private:
  std::vector<std::unique_ptr<DEAD_UI>> uis;
};
