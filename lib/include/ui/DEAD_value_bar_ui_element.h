#pragma once
#include "../DEAD_renderer.h"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <memory>
class DEAD_ValueBarUIElement {
public:
  DEAD_ValueBarUIElement(DEAD_Renderer* renderer, int x, int y,
                         int healthBarWidth, int healthBarHeight,
                         int distanceBetweenScreenBoarder, int boarderWidth);
  void render(SDL_Color baseColor, SDL_Color juiceColor, SDL_Color subColor,
              double percent, double subPercent);
  void render(SDL_Color baseColor, SDL_Color juiceColor, double percent);

private:
  DEAD_Renderer* renderer;
  SDL_Rect barRectBase;
  double percent;
  SDL_Rect barRectJuice;
  SDL_Rect barRectSub;
  double subPercent;
  int juiceMaxWidth;
  int barMaxWidth;
};
