#pragma once

#include <memory>

class DEAD_Renderer;
class DEAD_Game;

class DEAD_UI {
public:
  DEAD_UI(std::shared_ptr<DEAD_Renderer> renderer);
  virtual void render() = 0;
  virtual ~DEAD_UI();
protected:
  std::shared_ptr<DEAD_Game> game; 
  std::shared_ptr<DEAD_Renderer> renderer;
};
