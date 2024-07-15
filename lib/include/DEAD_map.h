#pragma once

#include <map>
#include <vector>

class DEAD_MapObjectBase;

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
  std::vector<std::vector<DEAD_MapObjectBase*>> getMapObjects();
  MapSize getMapSize();
private:
  std::vector<std::vector<DEAD_MapObjectBase*>> mapObjects;
  void loadMap();
  MapSize mapSize;
  
};
