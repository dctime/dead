#pragma once

#include <map>
#include <memory>
#include <set>
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
  std::vector<std::vector<std::shared_ptr<DEAD_MapObjectBase>>> getMapObjects();
  MapSize getMapSize();
  std::vector<DEAD_Map::MapLocation> getPlayerPointLocs();
private:
  std::vector<std::vector<std::shared_ptr<DEAD_MapObjectBase>>> mapObjects;
  void loadMap();
  bool isSquare();
  MapSize mapSize;
  std::vector<DEAD_Map::MapLocation> playerPointLocs;
  
};
