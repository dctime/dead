#include "DEAD_player.h"
#include "ui/DEAD_ui.h"
#include <DEAD_game.h>
#include <SDL2/SDL_render.h>
#include <memory>
#include <ui/DEAD_player_health_ui.h>

DEAD_PlayerHealthUI::DEAD_PlayerHealthUI(
    std::shared_ptr<DEAD_Renderer> renderer, std::shared_ptr<DEAD_Player> player)
    : DEAD_UI(renderer), healthBarWidth(this->game->SCREEN_WIDTH / 3),
      healthBarHeight(this->game->SCREEN_HEIGHT / 50),
      distanceBetweenScreenBoarder(10), boarderWidth(healthBarHeight / 4),
      player(player) {
}

void DEAD_PlayerHealthUI::render() {

  const SDL_Rect healthBarRectBase = {
      .x = this->game->SCREEN_WIDTH / 2 - this->healthBarWidth / 2,
      .y = this->game->SCREEN_HEIGHT - this->healthBarHeight -
           this->distanceBetweenScreenBoarder,
      .w = this->healthBarWidth,
      .h = this->healthBarHeight};

  double healthPercent = static_cast<double>(this->player->getHealth()) / this->player->getMaxhealth();

  const SDL_Rect healthBarRectJuice = {
      .x = healthBarRectBase.x + this->boarderWidth,
      .y = healthBarRectBase.y + this->boarderWidth,
      .w = (int)((healthBarRectBase.w - 2 * this->boarderWidth) * healthPercent),
      .h = healthBarRectBase.h - 2 * this->boarderWidth};

  SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), 50, 50, 50, 255);
  SDL_RenderFillRect(this->renderer->getSDLRenderer(), &healthBarRectBase);
  SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), 200, 15, 15, 255);
  SDL_RenderFillRect(this->renderer->getSDLRenderer(), &healthBarRectJuice);
}
