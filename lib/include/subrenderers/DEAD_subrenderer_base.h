#pragma once
class DEAD_Renderer;

class DEAD_SubRendererBase {
public:
  DEAD_SubRendererBase(DEAD_Renderer* renderer);
  virtual ~DEAD_SubRendererBase() {};
  virtual void render() = 0;
protected:
  DEAD_Renderer* renderer;
};
