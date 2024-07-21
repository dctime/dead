#include "DEAD_entity.h"
#include "DEAD_map.h"
#include "zombies/DEAD_zombie.h"
#include <DEAD_game.h>
#include <DEAD_zombie_director.h>
#include <climits>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <queue>
#include <set>
#include <stack>
#include <vector>

DEAD_ZombieDirector::DEAD_ZombieDirector(std::shared_ptr<DEAD_Game> game,
                                         int mapWidth, int mapHeight)
    : game(game) {
  for (int counterHeight = 0; counterHeight < mapHeight; counterHeight++) {
    std::vector<DEAD_ZombieDirector::ZombieMovementMapData> datas;
    for (int counterWidth = 0; counterWidth < mapWidth; counterWidth++) {
      DEAD_ZombieDirector::ZombieMovementMapData data;
      data.heatMapValue = INT_MAX;

      datas.push_back(data);
    }
    this->zombieMovementMap.push_back(datas);
  }

  
}

void DEAD_ZombieDirector::registerZombie(std::shared_ptr<DEAD_Zombie> zombie) {
  this->zombies.insert(zombie);
}

std::set<std::shared_ptr<DEAD_Zombie>> DEAD_ZombieDirector::getZombies() {
  return this->zombies;
}

void DEAD_ZombieDirector::tickZombies() {
  for (std::shared_ptr<DEAD_Zombie> zombie : this->zombies) {
    DEAD_ZombieDirector::ZombieVector moveVector = this->getLocMovementMapData(zombie->getPos().x, zombie->getPos().y).vector;
    zombie->move(moveVector.vectorX/10, moveVector.vectorY/10);
  }

}

void DEAD_ZombieDirector::updateHeatMapValue() {
  std::queue<std::vector<int>> calQueue;

  // for (std::vector<DEAD_ZombieDirector::ZombieMovementMapData> v :
  //      this->zombieMovementMap) {
  //   for (DEAD_ZombieDirector::ZombieMovementMapData d : v) {
  //     d.heatMapValue = -1;
  //   }
  // }

  DEAD_Map::MapLocation initLoc = this->game->getPlayer()->getPos();

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

    std::cout << "Heat Map: " << currentLoc[1] << ", " << currentLoc[0]
              << std::endl;

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
            ->isPlayerCollidable()) {
      calQueue.pop();
      continue;
    }
    if (visited.count(currentLocationOnly)) {
      std::cout << "Visited" << std::endl;
      if (this->zombieMovementMap[currentLoc[0]][currentLoc[1]].heatMapValue >
          currentLoc[2]) {
        this->zombieMovementMap[currentLoc[0]][currentLoc[1]].heatMapValue =
            currentLoc[2];
      }
      calQueue.pop();
      continue;
    }

    this->zombieMovementMap[currentLoc[0]][currentLoc[1]].heatMapValue =
        currentLoc[2];

    int pushSequenceSide[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int pushSequenceDia[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    for (int i = 0; i < 4; i++) {
      std::vector<int> pushLoc;
      pushLoc.push_back(pushSequenceSide[i][0] + currentLoc[0]);
      pushLoc.push_back(pushSequenceSide[i][1] + currentLoc[1]);
      pushLoc.push_back(currentLoc[2] + 1);
      std::cout << "Pushing: " << pushLoc[1] << ", " << pushLoc[0] << std::endl;

      calQueue.push(pushLoc);
    }

    // for (int i = 0; i < 4; i++) {
    //   std::vector<int> pushLoc;
    //   pushLoc.push_back(pushSequenceDia[i][0] + currentLoc[0]);
    //   pushLoc.push_back(pushSequenceDia[i][1] + currentLoc[1]);
    //   pushLoc.push_back(currentLoc[2]+2);
    //   std::cout << "Pushing: " << pushLoc[1] << ", " << pushLoc[0] <<
    //   std::endl;
    //
    //   calQueue.push(pushLoc);
    // }

    visited.insert(currentLocationOnly);
    calQueue.pop();

    // TODO: Implement Heat Map
  }

  int counter = 0;
  for (std::vector<DEAD_ZombieDirector::ZombieMovementMapData> v :
       this->zombieMovementMap) {
    for (DEAD_ZombieDirector::ZombieMovementMapData d : v) {
      if (d.heatMapValue == INT_MAX) {
        std::cout << std::setw(3) << "X";
        continue;
      }
      std::cout << std::setw(3) << d.heatMapValue;
    }
    std::cout << std::endl;
  }

  std::cout << counter << std::endl;
}

DEAD_ZombieDirector::ZombieMovementMapData
DEAD_ZombieDirector::getLocMovementMapData(int x, int y) {
  return this->zombieMovementMap.at(y).at(x);
}

void DEAD_ZombieDirector::setLocMovementMapData(
    int x, int y, DEAD_ZombieDirector::ZombieMovementMapData data) {
  this->zombieMovementMap.at(y).at(x) = data;
}

DEAD_ZombieDirector::ZombieVector
DEAD_ZombieDirector::getLocGradient(DEAD_ZombieDirector::ZombieMapLoc loc) {
  DEAD_ZombieDirector::ZombieVector returnVector;
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

  // Left
  if (check(loc.x - 1, loc.y, this->game))
    returnVector.vectorX +=
        func(this->getLocMovementMapData(loc.x - 1, loc.y).heatMapValue) * -1;

  if (check(loc.x + 1, loc.y, this->game))
    // Right
    returnVector.vectorX +=
        func(this->getLocMovementMapData(loc.x + 1, loc.y).heatMapValue) * 1;

  if (check(loc.x, loc.y + 1, this->game))
    // Up
    returnVector.vectorY +=
        func(this->getLocMovementMapData(loc.x, loc.y + 1).heatMapValue) * 1;

  if (check(loc.x, loc.y - 1, this->game))
    // Down
    returnVector.vectorY +=
        func(this->getLocMovementMapData(loc.x, loc.y - 1).heatMapValue) * -1;

  if (check(loc.x + 1, loc.y + 1, this->game)) {
    // Right Up
    returnVector.vectorX +=
        func(this->getLocMovementMapData(loc.x + 1, loc.y + 1).heatMapValue) *
        1 / sqrt(2);
    returnVector.vectorY +=
        func(this->getLocMovementMapData(loc.x + 1, loc.y + 1).heatMapValue) *
        1 / sqrt(2);
  }
  if (check(loc.x+1, loc.y-1, this->game)) {
  // Right Down
  returnVector.vectorX +=
      func(this->getLocMovementMapData(loc.x + 1, loc.y - 1).heatMapValue) * 1 /
      sqrt(2);
  returnVector.vectorY +=
      func(this->getLocMovementMapData(loc.x + 1, loc.y - 1).heatMapValue) *
      -1 / sqrt(2);
  }
  if (check(loc.x-1, loc.y+1, this->game)) {
  // Left Up
  returnVector.vectorX +=
      func(this->getLocMovementMapData(loc.x - 1, loc.y + 1).heatMapValue) *
      -1 / sqrt(2);
  returnVector.vectorY +=
      func(this->getLocMovementMapData(loc.x - 1, loc.y + 1).heatMapValue) * 1 /
      sqrt(2);
  }
  if (check(loc.x-1, loc.y-1, this->game)) {
  // Left Down
  returnVector.vectorX +=
      func(this->getLocMovementMapData(loc.x - 1, loc.y - 1).heatMapValue) *
      -1 / sqrt(2);
  returnVector.vectorY +=
      func(this->getLocMovementMapData(loc.x - 1, loc.y - 1).heatMapValue) *
      -1 / sqrt(2);
  }
  return returnVector;
}

void DEAD_ZombieDirector::updateZombieMapVector() {
  for (int y = 0; y < this->game->getMap()->getMapSize().height; y++) {
    for (int x = 0; x < this->game->getMap()->getMapSize().width; x++) {
      DEAD_ZombieDirector::ZombieMovementMapData data;
      data.heatMapValue = this->getLocMovementMapData(x, y).heatMapValue;
      DEAD_ZombieDirector::ZombieMapLoc loc = {.x = x, .y = y};
      data.vector = this->getLocGradient(loc);
      this->setLocMovementMapData(x, y, data);
    }
  }

  for (std::vector<DEAD_ZombieDirector::ZombieMovementMapData> v :
       this->zombieMovementMap) {
    for (DEAD_ZombieDirector::ZombieMovementMapData d : v) {
      std::cout << "(" << d.vector.vectorX << "," << d.vector.vectorY << ")";
    }
    std::cout << std::endl;
  }
}
