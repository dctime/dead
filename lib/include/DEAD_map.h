#pragma once

#include "DEAD_map.h"
#include "map_objects/DEAD_map_object_base.h"
#include <map>
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
  std::vector<std::vector<DEAD_MapObjectBase*>> getMapObjects();

private:
  std::vector<std::vector<DEAD_MapObjectBase*>> mapObjects;
  void loadMap();
  MapSize mapSize;
  
};
