#pragma once
#include "DEAD_zombie_movement_maps.h"
#include "zombies/DEAD_zombie.h"
#include <memory>
#include <set>
#include <vector>

class DEAD_ZombieDirector {
public:
  DEAD_ZombieDirector(DEAD_Game* game);
  void registerZombie(std::unique_ptr<DEAD_Zombie>& zombie);
  void killZombie(DEAD_Zombie* zombie);
  std::set<std::unique_ptr<DEAD_Zombie>>& getZombies();
  ZombieVector getMovementVector(double targetX, double targetY);
  DEAD_ZombieMovementMaps* getZombieMovementMaps();
  void tickZombies();

private:
  std::set<std::unique_ptr<DEAD_Zombie>> zombies;
  DEAD_Game* game;
  std::unique_ptr<DEAD_ZombieMovementMaps> zombieMovementMaps;
};
