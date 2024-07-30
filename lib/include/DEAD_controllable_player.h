#pragma once
#include "DEAD_player.h"
#include <SDL2/SDL_events.h>

class DEAD_ControllablePlayer : public DEAD_Player {
public:
  DEAD_ControllablePlayer(DEAD_Game* game);
  ~DEAD_ControllablePlayer();
  void playerEvents(SDL_Event event);
  void handleKeyState();
  void handlePlayerRotation();
  void setGame(DEAD_Game* game) override;
private:
  double baseSpeed;
};  
