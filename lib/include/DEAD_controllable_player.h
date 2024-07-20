#pragma once
#include "DEAD_player.h"
#include <SDL2/SDL_events.h>

class DEAD_ControllablePlayer : public DEAD_Player {
public:
  DEAD_ControllablePlayer();
  ~DEAD_ControllablePlayer();
  void playerEvents(SDL_Event event);
  void handleKeyState();
  void handlePlayerRotation();
private:
  double baseSpeed;
};  
