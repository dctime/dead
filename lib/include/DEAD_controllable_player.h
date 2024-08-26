#pragma once
#include "DEAD_player.h"
#include "decorations/DEAD_decoration_base.h"
#include "player_input_method/DEAD_player_input_method.h"
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
  void switchInputMethodTo3D();
  void switchInputMethodTo2D();
private:
  double baseSpeed;
  double pressTimeTicks;
  double lastTimePressTicks;
  bool isPressingUseKey;
  std::unique_ptr<DEAD_PlayerInputMethod> inputMethod;

  friend class DEAD_PlayerInputMethod;
};  
