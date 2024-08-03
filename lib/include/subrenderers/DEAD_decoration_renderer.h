#include "DEAD_ui_renderer.h"
class DEAD_DecorationRenderer : public DEAD_SubRendererBase {
public:
  DEAD_DecorationRenderer(DEAD_Renderer* renderer);
  void render() override;
private:
};
