#include "DEAD_guns.h"
#include "DEAD_player.h"

class DEAD_Pistol : public DEAD_Guns {
public:
  DEAD_Pistol(DEAD_Player* player);
  SDL_Rect getTextureRect() override;
};
