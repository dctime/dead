#pragma once

#include "DEAD_map_spawner.h"
#include "map_objects/DEAD_player_memoriable_object.h"
#include <map>
#include <memory>
#include <set>
#include <system_error>
#include <vector>

class DEAD_CursedDirt;
class DEAD_MapObjectBase;
class DEAD_LabelBase;

struct MapSize {
  int width;
  int height;
};

class DEAD_Map : std::enable_shared_from_this<DEAD_Map> {
public:
  struct MapLocation {
    double x;
    double y;

    bool operator<(const MapLocation &loc) const {
      return this->x < loc.x || (this->x == loc.x && this->y < loc.y);
    }
  };

  struct MapLine {
    MapLocation point1;
    MapLocation point2;
  };

  DEAD_Map();
  ~DEAD_Map();
  void mapUpdateSizeAndInfo();
  std::vector<std::vector<std::unique_ptr<DEAD_MapObjectBase>>> &
  getMapObjects();
  DEAD_MapObjectBase *getMapObject(int x, int y);
  DEAD_IPlayerMemoriableObject *getPlayerMemoriableObject(int x, int y);
  MapSize getMapSize();
  std::vector<DEAD_Map::MapLocation> getPlayerPointLocs();
  DEAD_MapSpawner *getMapSpawner();
  void loadMap();
  bool checkInMap(int x, int y);
  void updateMemoryObjects(int x, int y, int halfSize);
  void updatePointsAndLines();
  const std::vector<DEAD_Map::MapLine>& getLines();
  const std::set<DEAD_Map::MapLocation>& getPoints();

private:
  struct LineStatus {
    int leftLineIndex = -1;
    int rightLineIndex = -1;
    int upLineIndex = -1;
    int downLineIndex = -1;
  };

  class LocLineStatus {
  public:
    LocLineStatus(DEAD_Map *map) {
      for (int y = 0; y < map->getMapSize().height; y++) {
        std::vector<LineStatus> temp;
        for (int x = 0; x < map->getMapSize().width; x++) {
          LineStatus status;
          temp.push_back(status);
        }
        lineStatus.push_back(temp);
      }
    }

    LineStatus getLineStatus(int x, int y, DEAD_Map *map) {
      if ((x < 0 || x >= map->getMapSize().width) || y < 0 ||
          y >= map->getMapSize().height) {
        LineStatus status;
        return status;
      }

      return lineStatus.at(y).at(x);
    }

    LineStatus &setLineStatus(int x, int y) { return lineStatus.at(y).at(x); }

  private:
    std::vector<std::vector<LineStatus>> lineStatus;
  };
  std::vector<std::vector<std::unique_ptr<DEAD_MapObjectBase>>> mapObjects;
  bool isSquare();
  MapSize mapSize;
  std::vector<DEAD_Map::MapLocation> playerPointLocs;
  std::unique_ptr<DEAD_MapSpawner> mapSpawner;
  void initWithThis();
  std::vector<std::vector<DEAD_IPlayerMemoriableObject *>>
      playerMemoriableObjects;
  std::vector<DEAD_Map::MapLine> lines;
  std::set<DEAD_Map::MapLocation> points;

  template <typename T> void setHorizonVertical();
};
