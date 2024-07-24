#include "../DEAD_renderer.h"
#include <SDL2/SDL_rect.h>
#include <memory>
class DEAD_ValueBarUIElement {
public:
  DEAD_ValueBarUIElement(std::shared_ptr<DEAD_Renderer> renderer, int x, int y,
                         int healthBarWidth, int healthBarHeight,
                         int distanceBetweenScreenBoarder, int boarderWidth);
  void render();

private:
  std::shared_ptr<DEAD_Renderer> renderer;
  SDL_Rect healthBarRectBase;
  double healthPercent;
  SDL_Rect healthBarRectJuice;
  int juiceMaxWidth;
};
