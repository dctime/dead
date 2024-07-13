#include "DEAD_weapon.h"

class DEAD_Pistol : public DEAD_Weapon {
public:
  DEAD_Pistol(); 
  ~DEAD_Pistol();
  SDL_Rect getTextureRect() override;
};
