#include "DEAD_map.h"
#include "DEAD_zombie_director.h"
#include "zombies/DEAD_zombie.h"
#include <DEAD_map_spawner.h>
#include <SDL2/SDL_log.h>
#include <map_objects/DEAD_cursed_dirt.h>
#include <memory>
#include <random>
#include <vector>
#include <DEAD_game.h>


DEAD_MapSpawner::DEAD_MapSpawner() {
}

void DEAD_MapSpawner::addCurseDirt(std::shared_ptr<DEAD_CursedDirt> curseDirt) {
  this->curseDirts.push_back(curseDirt);
}

std::vector<std::shared_ptr<DEAD_CursedDirt>> DEAD_MapSpawner::getCursedDirts() {
  return this->curseDirts;
}

void DEAD_MapSpawner::initAccess(std::shared_ptr<DEAD_Game> game) {
  this->game = game;
}

void DEAD_MapSpawner::randomSpawnAZombie() {
  if (!this->curseDirts.size()) {
    SDL_Log("No curse dirt on the map. cannot spawn zombies");
    return;
  }
  std::random_device rd;
  std::uniform_int_distribution<int> dist(0, this->curseDirts.size()-1);
  DEAD_Map::MapLocation spawnLoc = this->curseDirts.at(dist(rd))->getLeftUpLoc();
  spawnLoc.x += 0.5;
  spawnLoc.y += 0.5;

  std::shared_ptr<DEAD_Zombie> zombie = std::make_shared<DEAD_Zombie>(this->game);
  zombie->setPos(spawnLoc.x, spawnLoc.y);
  this->game->getZombieDirector()->registerZombie(zombie);
}
