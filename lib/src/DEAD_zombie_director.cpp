#include "zombies/DEAD_zombie.h"
#include <DEAD_zombie_director.h>
#include <memory>
#include <set>

void DEAD_ZombieDirector::registerZombie(std::shared_ptr<DEAD_Zombie> zombie) {
  this->zombies.insert(zombie);
}

std::set<std::shared_ptr<DEAD_Zombie>> DEAD_ZombieDirector::getZombies() {
  return this->zombies;
}
