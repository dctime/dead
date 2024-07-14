#include "DEAD_bullet.h"
#include <memory>
#include <set>

class DEAD_BulletDirector {
public:
  void registerBullet(DEAD_Bullet* bullet);
  ~DEAD_BulletDirector();
  int bulletCount();
  std::set<DEAD_Bullet*> getBullets();
  void tickBullets();
private:
  std::set<DEAD_Bullet*> bullets; 
};
