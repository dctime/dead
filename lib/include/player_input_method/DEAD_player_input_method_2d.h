#include "DEAD_player_input_method.h"

class DEAD_PlayerInputMethod2D : public DEAD_PlayerInputMethod {
public:
  DEAD_PlayerInputMethod2D(DEAD_ControllablePlayer* player, double baseSpeed);
  void handleKeyState() override;
  void handlePlayerRotation() override;
private:
  double baseSpeed;
};
