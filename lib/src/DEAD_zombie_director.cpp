#include "DEAD_entity.h"
#include "DEAD_map.h"
#include "zombies/DEAD_zombie.h"
#include <DEAD_game.h>
#include <DEAD_zombie_director.h>
#include <climits>
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
      data.moveVectorX = 0;
      data.moveVectorY = 0;

      datas.push_back(data);
    }
    this->zombieMovementMap.push_back(datas);
  }

  this->updateHeatMapValue();
}

void DEAD_ZombieDirector::registerZombie(std::shared_ptr<DEAD_Zombie> zombie) {
  this->zombies.insert(zombie);
}

std::set<std::shared_ptr<DEAD_Zombie>> DEAD_ZombieDirector::getZombies() {
  return this->zombies;
}

void DEAD_ZombieDirector::updateHeatMapValue() {
  std::queue<std::vector<int>> calQueue;

  for (std::vector<DEAD_ZombieDirector::ZombieMovementMapData> v :
       this->zombieMovementMap) {
    for (DEAD_ZombieDirector::ZombieMovementMapData d : v) {
      // d.heatMapValue = INT_MAX;
      d.heatMapValue = 1;
    }
  }

  DEAD_Map::MapLocation initLoc = this->game->getPlayer()->getPos();

  std::vector<int> initLocVector;
  initLocVector.push_back(initLoc.y);
  initLocVector.push_back(initLoc.x);
  calQueue.push(initLocVector);

  std::set<std::vector<int>> visited;
  while (!calQueue.empty()) {
    std::vector<int> currentLoc = calQueue.front();
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
    if (visited.count(currentLoc)) {
      std::cout << "Visited" << std::endl;
      calQueue.pop();
      continue;
    }

    this->zombieMovementMap[currentLoc[0]][(int)currentLoc[1]].heatMapValue = 0;
    int pushSequence[8][2] = {{0, 1}, {1, 0},  {0, -1}, {-1, 0},
                              {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    for (int i = 0; i < 8; i++) {
      std::vector<int> pushLoc;
      pushLoc.push_back(pushSequence[i][0] + currentLoc[0]);
      pushLoc.push_back(pushSequence[i][1] + currentLoc[1]);
      std::cout << "Pushing: " << pushLoc[1] << ", " << pushLoc[0] << std::endl;

      calQueue.push(pushLoc);
    }

    visited.insert(currentLoc);
    calQueue.pop();

    // TODO: Implement Heat Map
  }

  int counter = 0;
  for (std::vector<DEAD_ZombieDirector::ZombieMovementMapData> v :
       this->zombieMovementMap) {
    for (DEAD_ZombieDirector::ZombieMovementMapData d : v) {
      if (d.heatMapValue == 0) {
        counter++;
      }
    }
  }

  std::cout << counter << std::endl;
}
