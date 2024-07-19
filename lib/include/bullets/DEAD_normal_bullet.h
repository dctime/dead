#include "DEAD_bullet.h"
#include <memory>

class DEAD_NormalBullet : public DEAD_Bullet {
public:
  DEAD_NormalBullet(std::shared_ptr<DEAD_Player> owner, std::shared_ptr<DEAD_Gun> gun);
  SDL_Rect getBulletTextureRect() override; 
  void registerBullet() override;
  double getBulletSize() override;
  void tickBullet() override;
private:
  
};
