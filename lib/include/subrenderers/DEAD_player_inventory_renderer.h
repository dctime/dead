#include "../DEAD_renderer.h"
#include "DEAD_ui_renderer.h"


class DEAD_Renderer;

class DEAD_PlayerInventoryRenderer : public DEAD_SubRendererBase {
public:
  DEAD_PlayerInventoryRenderer(DEAD_Renderer* renderer, SDL_Texture* itemTexture);
  void render() override;
private:
  int frameBoarderWidth;
  int frameWidth;
  SDL_Texture* itemTexture;
  void renderFrame();
  DEAD_ScreenLocationFromLeftDown frameLeftDownLoc;
};
