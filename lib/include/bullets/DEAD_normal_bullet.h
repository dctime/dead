#include "DEAD_bullet.h"
#include <memory>

class DEAD_NormalBullet : public DEAD_Bullet {
public:
  DEAD_NormalBullet(DEAD_Player* owner, DEAD_Gun* gun);
  SDL_Rect getBulletTextureRect() override; 
  double getBulletSize() override;
  void tickBullet() override;
private:
};
