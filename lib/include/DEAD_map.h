#pragma once

#include <vector>

class DEAD_Map {
public:
  DEAD_Map();
  ~DEAD_Map();
  void renderMap();
  


private:
  std::vector<std::vector<char>> mapObjects;
  void loadMap();
};
