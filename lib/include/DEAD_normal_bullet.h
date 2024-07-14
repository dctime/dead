#include "DEAD_bullet.h"

class DEAD_NormalBullet : public DEAD_Bullet {
public:
  DEAD_NormalBullet(DEAD_Player* owner);
  SDL_Rect getBulletTextureRect() override; 
  void registerBullet() override;
};
