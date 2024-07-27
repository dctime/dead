#include <DEAD_game.h>
#include <DEAD_map.h>
#include <DEAD_zombie_movement_maps.h>
#include <climits>
#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>


DEAD_ZombieMovementMaps::DEAD_ZombieMovementMaps(
    std::shared_ptr<DEAD_Game> game)
    : game(game) {
  MapSize mapSize = this->game->getMap()->getMapSize();
  int fullprocesses = mapSize.width * mapSize.height;
  int completeProcesses = 0;
  for (int y = 0; y < mapSize.height; y++) {
    std::vector<std::shared_ptr<DEAD_ZombieMovementMap>> mapRow;
    for (int x = 0; x < mapSize.width; x++) {
      mapRow.push_back(std::make_shared<DEAD_ZombieMovementMap>(game, x, y));
      completeProcesses++;
      std::cout << fullprocesses << " / " << completeProcesses << std::endl;
    }
    this->maps.push_back(mapRow);
  }
}

ZombieVector DEAD_ZombieMovementMaps::getMovementGradient(int playerX,
                                                          int playerY,
                                                          int zombieX,
                                                          int zombieY) {
  std::shared_ptr<DEAD_ZombieMovementMap> map =
      this->getZombieMovementMap(playerX, playerY);
  return map->getZombieMovementMapData(zombieX, zombieY).vector;
}

ZombieVector
DEAD_ZombieMovementMaps::getMovementGradient(ZombieMapLoc playerLoc,
                                             ZombieMapLoc zombieLoc) {
  return this->getMovementGradient(playerLoc.x, playerLoc.y, zombieLoc.x,
                                   zombieLoc.y);
}

std::shared_ptr<DEAD_ZombieMovementMap>
DEAD_ZombieMovementMaps::getZombieMovementMap(int x, int y) {
  return this->maps.at(y).at(x);
}

void DEAD_ZombieMovementMap::calAllGradients() {
  MapSize mapSize = this->game->getMap()->getMapSize();
  for (int y = 0; y < mapSize.height; y++) {
    for (int x = 0; x < mapSize.width; x++) {
      ZombieMapLoc currentLoc = {.x = x, .y = y};
      this->zombieMovementMap.at(y).at(x).vector = calLocGradient(currentLoc);
    }
  }
}

ZombieVector DEAD_ZombieMovementMap::calLocGradient(ZombieMapLoc loc) {
  ZombieVector returnVector;
  returnVector.vectorX = 0;
  returnVector.vectorY = 0;
  std::function<double(int)> func = [](int x) { return 1.0 / x; };
  std::function<bool(int, int, std::shared_ptr<DEAD_Game>)> check =
      [](int x, int y, std::shared_ptr<DEAD_Game> game) {
        if (x < 0 || x >= game->getMap()->getMapSize().width || y < 0 ||
            y >= game->getMap()->getMapSize().height)
          return false;
        else
          return true;
      };

  std::function<bool(int, int, std::shared_ptr<DEAD_Game>)> isNearbyWall =
      [check](int x, int y, std::shared_ptr<DEAD_Game> game) {
        int checkSequence[8][2] = {{1, 0}, {0, 1},  {-1, 0},  {0, -1},
                                   {1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

        for (int i = 0; i < 8; i++) {
          if (!check(x + checkSequence[i][1], y + checkSequence[i][0], game)) {
            return true;
          }

          if (check(x + checkSequence[i][1], y + checkSequence[i][0], game) &&
              game->getMap()
                  ->getMapObjects()
                  .at(y + checkSequence[i][0])
                  .at(x + checkSequence[i][1])
                  ->isZombieCollidable()) {
            return true;
          }
        }
        return false;
      };

  if (this->game->getMap()
          ->getMapObjects()
          .at(loc.y)
          .at(loc.x)
          ->isZombieCollidable()) {
    returnVector.vectorX = 0;
    returnVector.vectorY = 0;
    return returnVector;
  }

  if (isNearbyWall(loc.x, loc.y, this->game)) {
    int minHeatValue = INT_MAX;
    int checkSequence[8][2] = {{1, 0}, {0, 1},  {-1, 0},  {0, -1},
                               {1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
    for (int i = 0; i < 8; i++) {
      int locHeatValue = INT_MAX;
      if (check(loc.x + checkSequence[i][1], loc.y + checkSequence[i][0], game))
        locHeatValue =
            this->getZombieMovementMapData(loc.x + checkSequence[i][1],
                                           loc.y + checkSequence[i][0])
                .heatMapValue;
      if (locHeatValue < minHeatValue) {
        minHeatValue = locHeatValue;
        returnVector.vectorX = checkSequence[i][1];
        returnVector.vectorY = checkSequence[i][0];
      }
    }
    return returnVector;
  }

  // Left
  if (check(loc.x - 1, loc.y, this->game))
    returnVector.vectorX +=
        func(this->getZombieMovementMapData(loc.x - 1, loc.y).heatMapValue) *
        -1;

  if (check(loc.x + 1, loc.y, this->game))
    // Right
    returnVector.vectorX +=
        func(this->getZombieMovementMapData(loc.x + 1, loc.y).heatMapValue) * 1;

  if (check(loc.x, loc.y + 1, this->game))
    // Up
    returnVector.vectorY +=
        func(this->getZombieMovementMapData(loc.x, loc.y + 1).heatMapValue) * 1;

  if (check(loc.x, loc.y - 1, this->game))
    // Down
    returnVector.vectorY +=
        func(this->getZombieMovementMapData(loc.x, loc.y - 1).heatMapValue) *
        -1;

  if (check(loc.x + 1, loc.y + 1, this->game)) {
    // Right Up
    returnVector.vectorX +=
        func(
            this->getZombieMovementMapData(loc.x + 1, loc.y + 1).heatMapValue) *
        1 / sqrt(2);
    returnVector.vectorY +=
        func(
            this->getZombieMovementMapData(loc.x + 1, loc.y + 1).heatMapValue) *
        1 / sqrt(2);
  }
  if (check(loc.x + 1, loc.y - 1, this->game)) {
    // Right Down
    returnVector.vectorX +=
        func(
            this->getZombieMovementMapData(loc.x + 1, loc.y - 1).heatMapValue) *
        1 / sqrt(2);
    returnVector.vectorY +=
        func(
            this->getZombieMovementMapData(loc.x + 1, loc.y - 1).heatMapValue) *
        -1 / sqrt(2);
  }
  if (check(loc.x - 1, loc.y + 1, this->game)) {
    // Left Up
    returnVector.vectorX +=
        func(
            this->getZombieMovementMapData(loc.x - 1, loc.y + 1).heatMapValue) *
        -1 / sqrt(2);
    returnVector.vectorY +=
        func(
            this->getZombieMovementMapData(loc.x - 1, loc.y + 1).heatMapValue) *
        1 / sqrt(2);
  }
  if (check(loc.x - 1, loc.y - 1, this->game)) {
    // Left Down
    returnVector.vectorX +=
        func(
            this->getZombieMovementMapData(loc.x - 1, loc.y - 1).heatMapValue) *
        -1 / sqrt(2);
    returnVector.vectorY +=
        func(
            this->getZombieMovementMapData(loc.x - 1, loc.y - 1).heatMapValue) *
        -1 / sqrt(2);
  }

  double vectorLength =
      sqrt(pow(returnVector.vectorX, 2) + pow(returnVector.vectorY, 2));
  returnVector.vectorX = returnVector.vectorX / (vectorLength + 0.00001);
  returnVector.vectorY = returnVector.vectorY / (vectorLength + 0.00001);
  return returnVector;
}

void DEAD_ZombieMovementMap::calHeatMapValue() {
  std::queue<std::vector<int>> calQueue;

  DEAD_Map::MapLocation initLoc = {.x = this->x + 0.5, .y = this->y + 0.5};
  std::vector<std::vector<ZombieMovementMapData>> &returnMap =
      this->zombieMovementMap;

  std::vector<int> initLocVector;
  initLocVector.push_back(initLoc.y);
  initLocVector.push_back(initLoc.x);
  initLocVector.push_back(1); // HeatMap Value

  calQueue.push(initLocVector);

  std::set<std::vector<int>> visited;
  while (!calQueue.empty()) {

    std::vector<int> currentLoc = calQueue.front();

    std::vector<int> currentLocationOnly;
    currentLocationOnly.push_back(currentLoc[0]);
    currentLocationOnly.push_back(currentLoc[1]);

    // std::cout << "Heat Map: " << currentLoc[1] << ", " << currentLoc[0]
    //           << std::endl;

    if (currentLoc[1] < 0 ||
        currentLoc[1] >= this->game->getMap()->getMapSize().width) {
      calQueue.pop();
      continue;
    }

    if (currentLoc[0] < 0 ||
        currentLoc[0] >= this->game->getMap()->getMapSize().height) {
      calQueue.pop();
      continue;
    }
    if (this->game->getMap()
            ->getMapObjects()[(int)currentLoc[0]][(int)currentLoc[1]]
            ->isZombieCollidable()) {
      calQueue.pop();
      continue;
    }
    if (visited.count(currentLocationOnly)) {
      // std::cout << "Visited" << std::endl;
      if (returnMap.at(currentLoc[0]).at(currentLoc[1]).heatMapValue >
          currentLoc[2]) {
        returnMap.at(currentLoc[0]).at(currentLoc[1]).heatMapValue =
            currentLoc[2];
      }
      calQueue.pop();
      continue;
    }

    returnMap.at(currentLoc[0]).at(currentLoc[1]).heatMapValue = currentLoc[2];

    int pushSequenceSide[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int pushSequenceDia[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    for (int i = 0; i < 4; i++) {
      std::vector<int> pushLoc;
      pushLoc.push_back(pushSequenceSide[i][0] + currentLoc[0]);
      pushLoc.push_back(pushSequenceSide[i][1] + currentLoc[1]);
      pushLoc.push_back(currentLoc[2] + 1);
      // std::cout << "Pushing: " << pushLoc[1] << ", " << pushLoc[0] <<
      // std::endl;

      calQueue.push(pushLoc);
    }

    for (int i = 0; i < 4; i++) {
      std::vector<int> pushLoc;
      pushLoc.push_back(pushSequenceDia[i][0] + currentLoc[0]);
      pushLoc.push_back(pushSequenceDia[i][1] + currentLoc[1]);
      pushLoc.push_back(currentLoc[2] + 1);
      // std::cout << "Pushing: " << pushLoc[1] << ", " << pushLoc[0] <<
      // std::endl;

      calQueue.push(pushLoc);
    }

    visited.insert(currentLocationOnly);
    calQueue.pop();
  }

  // int counter = 0;
  // for (std::vector<DEAD_ZombieDirector::ZombieMovementMapData> v :
  //      this->zombieMovementMap) {
  //   for (DEAD_ZombieDirector::ZombieMovementMapData d : v) {
  //     if (d.heatMapValue == INT_MAX) {
  //       std::cout << std::setw(3) << "X";
  //       continue;
  //     }
  //     std::cout << std::setw(3) << d.heatMapValue;
  //   }
  //   std::cout << std::endl;
  // }
  //
  // std::cout << counter << std::endl;
}

DEAD_ZombieMovementMap::DEAD_ZombieMovementMap(std::shared_ptr<DEAD_Game> game,
                                               int x, int y)
    : game(game), x(x), y(y) {
  MapSize mapSize = this->game->getMap()->getMapSize();
  this->initMap(mapSize.width, mapSize.height);
  this->calHeatMapValue();
  this->calAllGradients();
}

ZombieMovementMapData DEAD_ZombieMovementMap::getZombieMovementMapData(int x,
                                                                       int y) {
  return this->zombieMovementMap.at(y).at(x);
}

void DEAD_ZombieMovementMap::initMap(int width, int height) {
  for (int counterHeight = 0; counterHeight < height; counterHeight++) {
    std::vector<ZombieMovementMapData> datas;
    for (int counterWidth = 0; counterWidth < width; counterWidth++) {
      ZombieMovementMapData data;
      data.heatMapValue = INT_MAX;

      datas.push_back(data);
    }
    this->zombieMovementMap.push_back(datas);
  }
}
