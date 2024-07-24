#include <DEAD_game.h>
#include <DEAD_renderer.h>
#include <memory>
#include <ui/DEAD_value_bar_ui_element.h>

DEAD_ValueBarUIElement::DEAD_ValueBarUIElement(
    std::shared_ptr<DEAD_Renderer> renderer, int x, int y, int healthBarWidth,
    int healthBarHeight, int distanceBetweenScreenBoarder, int boarderWidth) {
  this->renderer = renderer;
  this->barRectBase = {
      .x = x, .y = y, .w = healthBarWidth, .h = healthBarHeight};

  this->juiceMaxWidth = (int)((barRectBase.w - 2 * boarderWidth));
  this->barMaxWidth = (int)(barRectBase.w - 2 * boarderWidth);

  this->barRectJuice = {.x = barRectBase.x + boarderWidth,
                        .y = barRectBase.y + boarderWidth,
                        .w = (int)(juiceMaxWidth),
                        .h = barRectBase.h - 2 * boarderWidth};

  this->barRectSub = {.x = barRectBase.x + boarderWidth,
                      .y = barRectBase.y + boarderWidth,
                      .w = (int)(barMaxWidth),
                      .h = barRectBase.h / 8};
}
void DEAD_ValueBarUIElement::render(SDL_Color baseColor, SDL_Color juiceColor,
                                    double percent) {

  this->barRectJuice.w = this->juiceMaxWidth * percent;

  SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), baseColor.r,
                         baseColor.g, baseColor.b, baseColor.a);
  SDL_RenderFillRect(this->renderer->getSDLRenderer(), &barRectBase);
  SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), juiceColor.r,
                         juiceColor.g, juiceColor.b, juiceColor.a);
  SDL_RenderFillRect(this->renderer->getSDLRenderer(), &barRectJuice);
}
void DEAD_ValueBarUIElement::render(SDL_Color baseColor, SDL_Color juiceColor,
                                    SDL_Color subColor, double percent,
                                    double subPercent) {

  this->barRectJuice.w = this->juiceMaxWidth * percent;
  this->barRectSub.w = this->barMaxWidth * subPercent;

  SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), baseColor.r,
                         baseColor.g, baseColor.b, baseColor.a);
  SDL_RenderFillRect(this->renderer->getSDLRenderer(), &barRectBase);
  SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), juiceColor.r,
                         juiceColor.g, juiceColor.b, juiceColor.a);
  SDL_RenderFillRect(this->renderer->getSDLRenderer(), &barRectJuice);
  SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), subColor.r,
                         subColor.g, subColor.b, subColor.a);
  SDL_RenderFillRect(this->renderer->getSDLRenderer(), &barRectSub);
}
