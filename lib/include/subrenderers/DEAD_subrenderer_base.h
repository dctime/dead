#pragma once
class DEAD_Renderer;

class DEAD_SubRendererBase {
public:
  DEAD_SubRendererBase(DEAD_Renderer* renderer);
  virtual void render() = 0;
protected:
  DEAD_Renderer* renderer;
};
