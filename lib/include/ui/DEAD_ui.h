#pragma once

#include <memory>

class DEAD_Renderer;
class DEAD_Game;

class DEAD_UI {
public:
  DEAD_UI(DEAD_Renderer* renderer);
  virtual void render() = 0;
  virtual ~DEAD_UI();
protected:
  DEAD_Game* game; 
  DEAD_Renderer* renderer;
};
