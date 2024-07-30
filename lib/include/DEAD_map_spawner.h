#pragma once
#include <memory>
#include <vector>
class DEAD_CursedDirt;
class DEAD_Game;

class DEAD_MapSpawner {
public:
  DEAD_MapSpawner();
  void addCurseDirt(DEAD_CursedDirt* curseDirt);
  std::vector<DEAD_CursedDirt*> getCursedDirts();
  void initAccess(DEAD_Game* game);
  void randomSpawnAZombie();
private:
  DEAD_Game* game; 
  std::vector<DEAD_CursedDirt*> curseDirts;
};
