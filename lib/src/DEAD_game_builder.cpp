#include "DEAD_controllable_player.h"
#include "DEAD_game.h"
#include "DEAD_renderer.h"
#include <DEAD_game_builder.h>
#include <DEAD_player.h>
#include <memory>

DEAD_GameBuilder::DEAD_GameBuilder()
    : buildingGame(std::make_shared<DEAD_Game>()) {}

std::shared_ptr<DEAD_Game> DEAD_GameBuilder::build() {
  std::shared_ptr<DEAD_ControllablePlayer> player =
      std::make_shared<DEAD_ControllablePlayer>(this->buildingGame);
  this->buildingGame->setPlayer(player);

  player->setGame(this->buildingGame);
  this->buildingGame->initObjectThatHasSharedFromThis();
  std::shared_ptr<DEAD_Renderer> renderer = this->buildingGame->getRenderer();
  renderer->initWithSharedFromThis(renderer);

  return this->buildingGame;
}
