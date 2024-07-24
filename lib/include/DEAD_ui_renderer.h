#pragma once 
#include "ui/DEAD_ui.h"
#include <memory>
#include <vector>
class DEAD_UIRenderer {
public:
  DEAD_UIRenderer(std::shared_ptr<DEAD_Renderer> renderer);
  void render();
private:
  std::vector<std::shared_ptr<DEAD_UI>> uis;
};
