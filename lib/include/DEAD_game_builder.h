#pragma once
#include <memory>
#include "DEAD_game.h"

class DEAD_GameBuilder {
public:
  DEAD_GameBuilder(std::string playerName);
  std::unique_ptr<DEAD_Game> build();
private:
  std::unique_ptr<DEAD_Game> buildingGame;
};
