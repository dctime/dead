#include "DEAD_player.h"
#include "ui/DEAD_ui.h"
#include <DEAD_game.h>
#include <SDL2/SDL_render.h>
#include <memory>
#include <ui/DEAD_player_health_ui.h>

DEAD_PlayerHealthUI::DEAD_PlayerHealthUI(
    std::shared_ptr<DEAD_Renderer> renderer,
    std::shared_ptr<DEAD_Player> player)
    : DEAD_UI(renderer), healthBarWidth(this->game->SCREEN_WIDTH / 3),
      healthBarHeight(this->game->SCREEN_HEIGHT / 50),
      distanceBetweenScreenBoarder(10), boarderWidth(healthBarHeight / 4),
      player(player),
      barElement(std::make_shared<DEAD_ValueBarUIElement>(
          renderer, this->game->SCREEN_WIDTH / 2 - this->healthBarWidth / 2,
          this->game->SCREEN_HEIGHT - this->healthBarHeight -
              this->distanceBetweenScreenBoarder,
          healthBarWidth, healthBarHeight, distanceBetweenScreenBoarder,
          boarderWidth)) {}

void DEAD_PlayerHealthUI::render() {
  barElement->render();
}
