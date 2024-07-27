#pragma once
#include "DEAD_zombie_movement_maps.h"
#include "zombies/DEAD_zombie.h"
#include <memory>
#include <set>
#include <vector>

class DEAD_ZombieDirector {
public:
  DEAD_ZombieDirector(std::shared_ptr<DEAD_Game> game);
  void registerZombie(std::shared_ptr<DEAD_Zombie> zombie);
  void killZombie(std::shared_ptr<DEAD_Zombie> zombie);
  std::set<std::shared_ptr<DEAD_Zombie>> getZombies();
  ZombieVector getMovementVector(double targetX, double targetY);
  std::shared_ptr<DEAD_ZombieMovementMaps> getZombieMovementMaps();
  void tickZombies();

private:
  std::set<std::shared_ptr<DEAD_Zombie>> zombies;
  std::shared_ptr<DEAD_Game> game;
  std::shared_ptr<DEAD_ZombieMovementMaps> zombieMovementMaps;
};
