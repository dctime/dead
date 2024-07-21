#pragma once
#include <memory>
#include <set>
#include <vector>
#include "zombies/DEAD_zombie.h"


class DEAD_ZombieDirector {
public:
  struct ZombieVector {
    double vectorX;
    double vectorY;
  };

  struct ZombieMovementMapData {
    DEAD_ZombieDirector::ZombieVector vector;
    double heatMapValue;
  };

  struct ZombieMapLoc {
    int x;
    int y;
  };

  DEAD_ZombieDirector(std::shared_ptr<DEAD_Game> game, int mapWidth, int mapHeight);
  void registerZombie(std::shared_ptr<DEAD_Zombie> zombie);
  std::set<std::shared_ptr<DEAD_Zombie>> getZombies();
  void updateHeatMapValue();
  void updateZombieMapVector();
  DEAD_ZombieDirector::ZombieMovementMapData getLocMovementMapData(int x, int y);
  void setLocMovementMapData(int x, int y, DEAD_ZombieDirector::ZombieMovementMapData data);
  void tickZombies();
private:
  std::set<std::shared_ptr<DEAD_Zombie>> zombies;
  std::shared_ptr<DEAD_Game> game;
  std::vector<std::vector<ZombieMovementMapData>> zombieMovementMap;
  DEAD_ZombieDirector::ZombieVector getLocGradient(DEAD_ZombieDirector::ZombieMapLoc loc);
};

