#include "DEAD_bullet.h"

class DEAD_NormalBullet : public DEAD_Bullet {
public:
  DEAD_NormalBullet(DEAD_Player* owner);
  ~DEAD_NormalBullet();
  SDL_Rect getBulletTextureRect() override; 
};
