#pragma once
#include <memory>

class DEAD_ControllablePlayer;

class DEAD_PlayerInputMethod {
public:
  DEAD_PlayerInputMethod(DEAD_ControllablePlayer* player);
  virtual ~DEAD_PlayerInputMethod() {}
  virtual void handleKeyState() = 0;
  virtual void handlePlayerRotation() = 0;
protected:
  DEAD_ControllablePlayer* player;
};
