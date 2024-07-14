#include "DEAD_bullet.h"
#include <memory>
#include <set>

class DEAD_BulletDirector {
public:
  void registerBullet(DEAD_Bullet* bullet);
  int bulletCount();
private:
  std::set<DEAD_Bullet*> bullets; 
};
