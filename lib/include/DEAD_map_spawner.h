#pragma once
#include <memory>
#include <vector>
class DEAD_CursedDirt;
class DEAD_Game;

class DEAD_MapSpawner {
public:
  DEAD_MapSpawner();
  void addCurseDirt(std::shared_ptr<DEAD_CursedDirt> curseDirt);
  std::vector<std::shared_ptr<DEAD_CursedDirt>> getCursedDirts();
  void initAccess(std::shared_ptr<DEAD_Game> game);
  void randomSpawnAZombie();
private:
  std::shared_ptr<DEAD_Game> game; 
  std::vector<std::shared_ptr<DEAD_CursedDirt>> curseDirts;
};
