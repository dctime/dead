#pragma once
#include "DEAD_player.h"
#include "decorations/DEAD_decoration_base.h"
#include <SDL2/SDL_events.h>

class DEAD_ControllablePlayer : public DEAD_Player {
public:
  DEAD_ControllablePlayer(DEAD_Game* game, std::string playerName);
  ~DEAD_ControllablePlayer();
  void playerEvents(SDL_Event event);
  void handleKeyState();
  void handlePlayerRotation();
  void setGame(DEAD_Game* game) override;
  void updatePressUseTimeTicks();
  bool getIsPressingUseKey();
  void resetLastTimePressTicks();
private:
  double baseSpeed;
  double pressTimeTicks;
  double lastTimePressTicks;
  bool isPressingUseKey;
};  
