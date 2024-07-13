#include "DEAD_guns.h"

class DEAD_Shotgun : public DEAD_Guns{
public:
  DEAD_Shotgun();
  ~DEAD_Shotgun();
  SDL_Rect getTextureRect() override;
};
