#include "DEAD_map_spawner.h"
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
  this->mapSpawner = std::make_unique<DEAD_MapSpawner>();
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
    std::vector<std::unique_ptr<DEAD_MapObjectBase>> temp;
    std::unique_ptr<DEAD_MapObjectBase> obj;
    for (char c : line) {
      x += 1;
      DEAD_Map::MapLocation loc = {.x=(double)x, .y=(double)y};
      DEAD_Map::MapLocation insertRect = {.x=loc.x+0.5 ,.y=loc.y+0.5};
      switch (c) {
        case 'w':
          obj = std::make_unique<DEAD_Wood>(loc);
          break;
        case 's':
          obj = std::make_unique<DEAD_Stone>(loc);
          break;
        case ' ':
          obj = std::make_unique<DEAD_Air>(loc);
          break;
        case 'c':
          obj = std::make_unique<DEAD_CursedDirt>(loc);
          this->mapSpawner->addCurseDirt(static_cast<DEAD_CursedDirt*>(obj.get()));
          break;
        case 'p':
          obj = std::make_unique<DEAD_Point>(loc);
          this->playerPointLocs.push_back(insertRect);
          break;
        default:
          SDL_Log("Unknown Symbol in Map File");
          obj = nullptr;
      }
      temp.push_back(std::move(obj));
    }
    this->mapObjects.push_back(std::move(temp));
    if (this->playerPointLocs.size() > 1) {
      SDL_Log("There should only be a Point 'p' on a map");
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
  for (int y = 0; y < this->mapObjects.size(); y++) {
    if (this->mapSize.width < (int) this->mapObjects.at(y).size()) { this->mapSize.width = this->mapObjects.at(y).size(); }
    for (std::unique_ptr<DEAD_MapObjectBase>& c : this->mapObjects.at(y)) {
      std::cout << c->getChar();
    }
    std::cout << std::endl;
  }
  this->mapSize.height = this->mapObjects.size();
  
  std::string sizeMessage = 
    ("Map Size: " + std::to_string(this->mapSize.width) + "*" + std::to_string(this->mapSize.height)).c_str();
  std::cout << sizeMessage << std::endl;
  SDL_Log("%s", sizeMessage.c_str());
  std::cout << "Height: " << this->mapSize.height << "Width: " << this->mapSize.width << std::endl;
}

bool DEAD_Map::isSquare() {
  if (this->mapSize.height <= 0) return true;

  for (int y = 0; y < this->mapObjects.size(); y++) {
    std::cout << "v.size(): " << this->mapObjects.at(y).size() << std::endl;
    if (this->mapObjects.at(y).size() != this->mapSize.width) return false;
  }

  
  return true;
}

std::vector<std::vector<std::unique_ptr<DEAD_MapObjectBase>>>& DEAD_Map::getMapObjects() {
  return this->mapObjects;
}

MapSize DEAD_Map::getMapSize() { return this->mapSize; }

std::vector<DEAD_Map::MapLocation> DEAD_Map::getPlayerPointLocs() {
  return this->playerPointLocs;
}

DEAD_MapSpawner* DEAD_Map::getMapSpawner() {
  return this->mapSpawner.get();
}

