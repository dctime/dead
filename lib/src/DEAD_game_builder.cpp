#include "DEAD_game.h"
#include "DEAD_renderer.h"
#include <DEAD_game_builder.h>
#include <DEAD_player.h>
#include <memory>

DEAD_GameBuilder::DEAD_GameBuilder(std::string playerName)
    : buildingGame(std::make_unique<DEAD_Game>(playerName)) {}

std::unique_ptr<DEAD_Game> DEAD_GameBuilder::build() {
  DEAD_Renderer* renderer = this->buildingGame->getRenderer();
  renderer->initWithSharedFromThis(renderer);

  return std::move(this->buildingGame);
}
