#include "DEAD_bullets.h"

class DEAD_NormalBullet : public DEAD_Bullets {
public:
  DEAD_NormalBullet();
  ~DEAD_NormalBullet();
  SDL_Rect getBulletTextureRect() override; 
};
