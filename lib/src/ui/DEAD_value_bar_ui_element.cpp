#include <DEAD_game.h>
#include <DEAD_renderer.h>
#include <memory>
#include <ui/DEAD_value_bar_ui_element.h>

DEAD_ValueBarUIElement::DEAD_ValueBarUIElement(
    std::shared_ptr<DEAD_Renderer> renderer, int x, int y, int healthBarWidth,
    int healthBarHeight, int distanceBetweenScreenBoarder, int boarderWidth) {
  this->renderer = renderer;
  this->healthBarRectBase = {
      .x = x,
      .y = y,
      .w = healthBarWidth,
      .h = healthBarHeight};

  double healthPercent =
      static_cast<double>(renderer->getGame()->getPlayer()->getHealth()) /
      renderer->getGame()->getPlayer()->getMaxhealth();

  this->healthBarRectJuice = {
      .x = healthBarRectBase.x + boarderWidth,
      .y = healthBarRectBase.y + boarderWidth,
      .w = (int)((healthBarRectBase.w - 2 * boarderWidth) * healthPercent),
      .h = healthBarRectBase.h - 2 * boarderWidth};
  this->juiceMaxWidth =
      (int)((healthBarRectBase.w - 2 * boarderWidth) * healthPercent);
}

void DEAD_ValueBarUIElement::render(SDL_Color baseColor, SDL_Color juiceColor, double percent) {
  
  this->healthBarRectJuice.w = this->juiceMaxWidth * percent;

  SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), baseColor.r, baseColor.g, baseColor.b, baseColor.a);
  SDL_RenderFillRect(this->renderer->getSDLRenderer(), &healthBarRectBase);
  SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), juiceColor.r, juiceColor.g, juiceColor.b, juiceColor.a);
  SDL_RenderFillRect(this->renderer->getSDLRenderer(), &healthBarRectJuice);
}
