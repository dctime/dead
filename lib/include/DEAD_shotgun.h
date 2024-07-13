#include "DEAD_gun.h"

class DEAD_Shotgun : public DEAD_Gun{
public:
  DEAD_Shotgun();
  ~DEAD_Shotgun();
  SDL_Rect getTextureRect() override;
};
