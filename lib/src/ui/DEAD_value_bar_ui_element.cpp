#include <DEAD_game.h>
#include <DEAD_renderer.h>
#include <memory>
#include <ui/DEAD_value_bar_ui_element.h>

DEAD_ValueBarUIElement::DEAD_ValueBarUIElement(
    std::shared_ptr<DEAD_Renderer> renderer, int x, int y, int healthBarWidth,
    int healthBarHeight, int distanceBetweenScreenBoarder, int boarderWidth) {
  this->renderer = renderer;
  this->healthBarRectBase = {
      .x = renderer->getGame()->SCREEN_WIDTH / 2 - healthBarWidth / 2,
      .y = renderer->getGame()->SCREEN_HEIGHT - healthBarHeight -
           distanceBetweenScreenBoarder,
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

void DEAD_ValueBarUIElement::render() {
  double healthPercent =
      static_cast<double>(renderer->getGame()->getPlayer()->getHealth()) /
      renderer->getGame()->getPlayer()->getMaxhealth();
  this->healthBarRectJuice.w = this->juiceMaxWidth * healthPercent;

  SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), 50, 50, 50, 255);
  SDL_RenderFillRect(this->renderer->getSDLRenderer(), &healthBarRectBase);
  SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), 200, 15, 15, 255);
  SDL_RenderFillRect(this->renderer->getSDLRenderer(), &healthBarRectJuice);
}
