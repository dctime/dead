#include "DEAD_entity.h"
#include "DEAD_map.h"
#include "DEAD_player.h"
#include "zombies/DEAD_zombie.h"
#include <DEAD_collision_director.h>
#include <DEAD_functions.h>
#include <DEAD_game.h>
#include <DEAD_zombie_director.h>
#include <DEAD_zombie_movement_maps.h>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <set>
#include <vector>

DEAD_ZombieDirector::DEAD_ZombieDirector(std::shared_ptr<DEAD_Game> game)
    : game(game),
      zombieMovementMaps(std::make_shared<DEAD_ZombieMovementMaps>(game)) {}

void DEAD_ZombieDirector::registerZombie(std::shared_ptr<DEAD_Zombie> zombie) {
  this->zombies.insert(zombie);
}

void DEAD_ZombieDirector::killZombie(std::shared_ptr<DEAD_Zombie> zombie) {
  this->zombies.erase(zombie);
}

std::set<std::shared_ptr<DEAD_Zombie>> DEAD_ZombieDirector::getZombies() {
  return this->zombies;
}

std::shared_ptr<DEAD_ZombieMovementMaps>
DEAD_ZombieDirector::getZombieMovementMaps() {
  return this->zombieMovementMaps;
}

void DEAD_ZombieDirector::tickZombies() {
  DEAD_Map::MapLocation playerLoc = this->game->getPlayer()->getPos();
  std::vector<std::shared_ptr<DEAD_Zombie>> deadZombies;
  for (std::shared_ptr<DEAD_Zombie> zombie : this->zombies) {
    if (zombie->getHealth() <= 0) {
      deadZombies.push_back(zombie);
    }
  }

  for (std::shared_ptr<DEAD_Zombie> deadZombie : deadZombies) {
    this->game->getZombieDirector()->killZombie(deadZombie);
  }

  for (std::shared_ptr<DEAD_Zombie> zombie : this->zombies) {
    double distanceBetween = DEAD_Functions::calDistance(
        zombie->getPos().x, zombie->getPos().y, playerLoc.x, playerLoc.y);
    if (distanceBetween < 1.414) {
      double moveXVec = zombie->getPos().x - playerLoc.x;
      double moveYVec = zombie->getPos().y - playerLoc.y;
      double deltaX = -moveXVec / distanceBetween / 100.0;
      double deltaY = -moveYVec / distanceBetween / 100.0;
      if (!(this->game->getCollisionDirector()
                ->entityCheckCollision(zombie, deltaX, deltaY)
                .size())) {
        zombie->move(deltaX, 0);
        zombie->move(0, deltaY);
        zombie->bite(this->game->getPlayer());
        continue;
      }
    }
    ZombieVector moveVector =
        this->getMovementVector(zombie->getPos().x, zombie->getPos().y);
    // std::cout << "Move vector: " << moveVector.vectorX << ", " <<
    // moveVector.vectorY << std::endl;
    zombie->move(moveVector.vectorX / 100, 0);
    zombie->move(0, moveVector.vectorY / 100);
  }
}

ZombieVector DEAD_ZombieDirector::getMovementVector(double targetX,
                                                    double targetY) {

  double baseX = (int)targetX;
  double baseY = (int)targetY;

  std::function<double(double, double, double, double)> calDistance =
      [](double x1, double x2, double y1, double y2) {
        return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
      };
  std::function<bool(int, int, std::shared_ptr<DEAD_Game>)> check =
      [](int x, int y, std::shared_ptr<DEAD_Game> game) {
        if (x < 0 || x >= game->getMap()->getMapSize().width || y < 0 ||
            y >= game->getMap()->getMapSize().height)
          return false;
        else
          return true;
      };

  ZombieVector returnVector;
  returnVector.vectorX = 0;
  returnVector.vectorY = 0;

  std::vector<ZombieVector> sequence;

  for (int multiplyCounter = 0; multiplyCounter < 10; multiplyCounter++)
    sequence.push_back({.vectorX = baseX, .vectorY = baseY});

  sequence.push_back({.vectorX = baseX + 1, .vectorY = baseY});
  sequence.push_back({.vectorX = baseX, .vectorY = baseY + 1});
  sequence.push_back({.vectorX = baseX - 1, .vectorY = baseY});
  sequence.push_back({.vectorX = baseX, .vectorY = baseY - 1});
  // sequence.push_back({.vectorX=baseX+1, .vectorY=baseY+1});
  // sequence.push_back({.vectorX=baseX+1, .vectorY=baseY-1});
  // sequence.push_back({.vectorX=baseX-1, .vectorY=baseY+1});
  // sequence.push_back({.vectorX=baseX-1, .vectorY=baseY-1});

  DEAD_Map::MapLocation playerLoc = this->game->getPlayer()->getPos();
  for (ZombieVector step : sequence) {
    if (!check(step.vectorX, step.vectorY, this->game))
      continue;
    double weight = calDistance(targetX, step.vectorX, targetY, step.vectorY);
    ZombieVector elementVector = this->zombieMovementMaps->getMovementGradient(
        playerLoc.x, playerLoc.y, step.vectorX, step.vectorY);
    returnVector.vectorX += elementVector.vectorX * weight;
    returnVector.vectorY += elementVector.vectorY * weight;
  }

  double vectorLength =
      sqrt(pow(returnVector.vectorX, 2) + pow(returnVector.vectorY, 2));
  returnVector.vectorX = returnVector.vectorX / (vectorLength + 0.000001);
  returnVector.vectorY = returnVector.vectorY / (vectorLength + 0.000001);
  return returnVector;
}
