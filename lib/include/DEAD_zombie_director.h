#pragma once
#include <memory>
#include <set>
#include <vector>
#include "zombies/DEAD_zombie.h"


class DEAD_ZombieDirector {
public:
  struct ZombieMovementMapData {
    double moveVectorX;
    double moveVectorY;
    double heatMapValue;
  };
  DEAD_ZombieDirector(std::shared_ptr<DEAD_Game> game, int mapWidth, int mapHeight);
  void registerZombie(std::shared_ptr<DEAD_Zombie> zombie);
  std::set<std::shared_ptr<DEAD_Zombie>> getZombies();
  void updateHeatMapValue();
private:
  std::set<std::shared_ptr<DEAD_Zombie>> zombies;
  std::shared_ptr<DEAD_Game> game;
  std::vector<std::vector<ZombieMovementMapData>> zombieMovementMap;
};

