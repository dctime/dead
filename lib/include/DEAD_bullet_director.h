#include "DEAD_bullet.h"
#include <set>

class DEAD_BulletDirector {
public:
  void registerBullet(DEAD_Bullet* bullet);
private:
  std::set<DEAD_Bullet*> bullets; 
};
