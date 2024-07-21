#pragma once
#include <memory>
#include "DEAD_game.h"

class DEAD_GameBuilder {
public:
  DEAD_GameBuilder();
  std::shared_ptr<DEAD_Game> build();
private:
  std::shared_ptr<DEAD_Game> buildingGame;
};
