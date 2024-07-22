#include "map_objects/DEAD_map_object_base.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <cstdio>
#include <fstream>
#include <memory>
#include <string>
#include <iostream>
#include <DEAD_map.h>
#include <DEAD_filepaths.h>
#include <map_objects/DEAD_wood.h>
#include <map_objects/DEAD_stone.h>
#include <map_objects/DEAD_air.h>
#include <map_objects/DEAD_point.h>
#include <map_objects/DEAD_cursed_dirt.h>
#include <vector>

DEAD_Map::DEAD_Map() {
  SDL_Log("Map Init");
  this->loadMap();
}

DEAD_Map::~DEAD_Map() {
  SDL_Log("Map Destoryed");
}

void DEAD_Map::loadMap() {
  this->mapObjects.clear();
  const char* inputFilePath = DEAD_FilePaths::MAP_FILE_PATH.c_str();
  std::ifstream inputFile(inputFilePath);
  std::string line;
  
  int x = -1;
  int y = -1;
  while (getline(inputFile, line)) {
    y += 1;
    std::vector<std::shared_ptr<DEAD_MapObjectBase>> temp;
    std::shared_ptr<DEAD_MapObjectBase> obj;
    for (char c : line) {
      x += 1;
      DEAD_Map::MapLocation loc = {.x=(double)x, .y=(double)y};
      DEAD_Map::MapLocation insertRect = {.x=loc.x+0.5 ,.y=loc.y+0.5};
      switch (c) {
        case 'w':
          obj = std::make_shared<DEAD_Wood>(loc);
          break;
        case 's':
          obj = std::make_shared<DEAD_Stone>(loc);
          break;
        case ' ':
          obj = std::make_shared<DEAD_Air>(loc);
          break;
        case 'c':
          obj = std::make_shared<DEAD_CursedDirt>(loc);
          this->curseDirts.push_back(std::dynamic_pointer_cast<DEAD_CursedDirt>(obj));
          break;
        case 'p':
          obj = std::make_shared<DEAD_Point>(loc);
          this->playerPointLocs.push_back(insertRect);
          break;
        default:
          SDL_Log("Unknown Symbol in Map File");
          obj = nullptr;
      }
      temp.push_back(obj);
    }
    this->mapObjects.push_back(temp);
    if (this->playerPointLocs.size() > 1) {
      SDL_Log("There should only be a Point 'p' on a map");
    }

    if (this->curseDirts.size() <= 0) {
      SDL_Log("There should be at least one cursed dirt to spawn zombies");
    }
    x = -1;
  }
  
  inputFile.close();
  this->mapUpdateSizeAndInfo();

  if (!this->isSquare()) {
    this->mapObjects.clear();
    this->mapSize.width = 0;
    this->mapSize.height = 0;
    SDL_Log("Map File Not Square");
  }

}

void DEAD_Map::mapUpdateSizeAndInfo() {
  this->mapSize.width = 0;
  for (std::vector<std::shared_ptr<DEAD_MapObjectBase>> v : this->mapObjects) {
    if (this->mapSize.width < (int) v.size()) { this->mapSize.width = v.size(); }
    for (std::shared_ptr<DEAD_MapObjectBase> c : v) {
      std::cout << c->getChar();
    }
    std::cout << std::endl;
  }
  this->mapSize.height = this->mapObjects.size();
  
  std::string sizeMessage = 
    ("Map Size: " + std::to_string(this->mapSize.width) + "*" + std::to_string(this->mapSize.height)).c_str();
  std::cout << sizeMessage << std::endl;
  SDL_Log("%s", sizeMessage.c_str());
}

bool DEAD_Map::isSquare() {
  if (this->mapSize.height <= 0) return true;

  for (std::vector<std::shared_ptr<DEAD_MapObjectBase>> v : this->mapObjects) {
    std::cout << "v.size(): " << v.size() << std::endl;
    if (v.size() != this->mapSize.width) return false;
  }

  
  return true;
}

std::vector<std::vector<std::shared_ptr<DEAD_MapObjectBase>>> DEAD_Map::getMapObjects() {
  return this->mapObjects;
}

MapSize DEAD_Map::getMapSize() { return this->mapSize; }

std::vector<DEAD_Map::MapLocation> DEAD_Map::getPlayerPointLocs() {
  return this->playerPointLocs;
}

