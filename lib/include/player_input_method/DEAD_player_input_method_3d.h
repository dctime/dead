#include "DEAD_player_input_method.h"
class DEAD_PlayerInputMethod3D : public DEAD_PlayerInputMethod {
public:
  DEAD_PlayerInputMethod3D(DEAD_ControllablePlayer* player, double baseSpeed);
  void handlePlayerRotation() override;
  void handleKeyState() override;
private:
  double baseSpeed;
  bool mouseRelative;
};
