#include "../DEAD_renderer.h"


class DEAD_Renderer;

class DEAD_PlayerInventoryRenderer {
public:
  DEAD_PlayerInventoryRenderer(DEAD_Renderer* renderer, SDL_Texture* itemTexture);
  void render();
private:
  DEAD_Renderer* renderer;
  int frameBoarderWidth;
  int frameWidth;
  SDL_Texture* itemTexture;
  void renderFrame();
  DEAD_ScreenLocationFromLeftDown frameLeftDownLoc;
};
