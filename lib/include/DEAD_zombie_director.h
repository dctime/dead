#pragma once
#include <memory>
#include <set>
#include "zombies/DEAD_zombie.h"


class DEAD_ZombieDirector {
public:
  void registerZombie(std::shared_ptr<DEAD_Zombie> zombie);
  std::set<std::shared_ptr<DEAD_Zombie>> getZombies();
private:
  std::set<std::shared_ptr<DEAD_Zombie>> zombies;
};

