#include "DEAD_gun.h"
#include "DEAD_player.h"

class DEAD_Pistol : public DEAD_Gun {
public:
  DEAD_Pistol(DEAD_Player* player);
  SDL_Rect getTextureRect() override;
  void attack() override;
  double getBarrelLength() override; 
};
