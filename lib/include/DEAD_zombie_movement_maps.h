#pragma once
#include <memory>
#include <vector>

class DEAD_Game;
class DEAD_ZombieMovementMap;

struct ZombieVector {
    double vectorX;
    double vectorY;
  };

  struct ZombieMovementMapData {
    ZombieVector vector;
    double heatMapValue;
  };

  struct ZombieMapLoc {
    int x;
    int y;
  };

class DEAD_ZombieMovementMaps {
public:
  DEAD_ZombieMovementMaps(DEAD_Game* game);
  ZombieVector getMovementGradient(ZombieMapLoc playerLoc, ZombieMapLoc zombieLoc);
  ZombieVector getMovementGradient(int playerX, int playerY, int zombieX, int zombieY);
  DEAD_ZombieMovementMap* getZombieMovementMap(int x, int y);
private:
  DEAD_Game* game;
  std::vector<std::vector<std::unique_ptr<DEAD_ZombieMovementMap>>> maps;
};

class DEAD_ZombieMovementMap {
public:
  DEAD_ZombieMovementMap(DEAD_Game* game, int x, int y);
  ZombieMovementMapData getZombieMovementMapData(int x, int y);
  void initMap(int width, int height);
  void calHeatMapValue();
  ZombieVector calLocGradient(ZombieMapLoc loc);
  void calAllGradients();
private:
  std::vector<std::vector<ZombieMovementMapData>> zombieMovementMap;
  int x;
  int y;
  DEAD_Game* game;

  friend class DEAD_ZombieMovementMaps;
};
