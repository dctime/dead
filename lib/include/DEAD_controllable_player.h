#pragma once
#include "DEAD_player.h"
#include <SDL2/SDL_events.h>

class DEAD_ControllablePlayer : public DEAD_Player {
public:
  DEAD_ControllablePlayer(std::shared_ptr<DEAD_Game> game);
  ~DEAD_ControllablePlayer();
  void playerEvents(SDL_Event event);
  void handleKeyState();
  void handlePlayerRotation();
  void setGame(std::shared_ptr<DEAD_Game> game) override;
private:
  double baseSpeed;
};  
