#pragma once

#include <vector>

struct MapSize {
  int width;
  int height;
};

class DEAD_Map {
public:
  struct MapLocation {
    double x;
    double y;
  };
  DEAD_Map();
  ~DEAD_Map();
  void mapUpdateSizeAndInfo(); 
  std::vector<std::vector<char>> getMapObjects();

private:
  std::vector<std::vector<char>> mapObjects;
  void loadMap();
  MapSize mapSize;
  
};
