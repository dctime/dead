#include <DEAD_zombie_director.h>

void DEAD_ZombieDirector::registerZombie(std::shared_ptr<DEAD_Zombie> zombie) {
  this->zombies.insert(zombie);
}
