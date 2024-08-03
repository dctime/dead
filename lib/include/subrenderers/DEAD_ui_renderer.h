#pragma once 
#include "../ui/DEAD_ui.h"
#include <memory>
#include <vector>
class DEAD_UIRenderer {
public:
  DEAD_UIRenderer(DEAD_Renderer* renderer);
  void render();
private:
  std::vector<std::unique_ptr<DEAD_UI>> uis;
};
