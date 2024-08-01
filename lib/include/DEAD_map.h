#pragma once

#include <map>
#include <memory>
#include <set>
#include <vector>
#include "DEAD_map_spawner.h"

class DEAD_CursedDirt;
class DEAD_MapObjectBase;
struct MapSize {
  int width;
  int height;
};

class DEAD_Map : std::enable_shared_from_this<DEAD_Map> {
public:
  struct MapLocation {
    double x;
    double y;
  };
  DEAD_Map();
  ~DEAD_Map();
  void mapUpdateSizeAndInfo(); 
  std::vector<std::vector<std::unique_ptr<DEAD_MapObjectBase>>>& getMapObjects();
  MapSize getMapSize();
  std::vector<DEAD_Map::MapLocation> getPlayerPointLocs();
  DEAD_MapSpawner* getMapSpawner();
  void loadMap();
  bool checkInMap(int x, int y);
private:
  std::vector<std::vector<std::unique_ptr<DEAD_MapObjectBase>>> mapObjects;
  bool isSquare();
  MapSize mapSize;
  std::vector<DEAD_Map::MapLocation> playerPointLocs;
  std::unique_ptr<DEAD_MapSpawner> mapSpawner; 
  void initWithThis();

  template<typename T>
  void setHorizonVertical();
  
};
