#include "DEAD_game.h"
#include <DEAD_game_builder.h>
#include <memory>

DEAD_GameBuilder::DEAD_GameBuilder(std::shared_ptr<DEAD_ControllablePlayer> player) 
  : buildingGame(std::make_shared<DEAD_Game>(player)) {
}

std::shared_ptr<DEAD_Game> DEAD_GameBuilder::build() {
  this->buildingGame->initObjectThatHasSharedFromThis();
  return this->buildingGame;
}
