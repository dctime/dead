#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <cstdio>
#include <fstream>
#include <string>
#include <iostream>
#include <DEAD_map.h>
#include <DEAD_filepaths.h>
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

  while (getline(inputFile, line)) {
    std::vector<char> temp;
    for (char c : line) {
      temp.push_back(c);
    }
    this->mapObjects.push_back(temp);

  }
  
  inputFile.close();
  this->mapUpdateSizeAndInfo();
}

void DEAD_Map::mapUpdateSizeAndInfo() {
  this->mapSize.width = -1;
  for (std::vector<char> v : this->mapObjects) {
    if (this->mapSize.width < (int) v.size()) { this->mapSize.width = v.size(); }
    for (char c : v) {
      std::cout << c;
    }
    std::cout << std::endl;
  }
  this->mapSize.height = this->mapObjects.size();
  
  std::string sizeMessage = 
    ("Map Size: " + std::to_string(this->mapSize.width) + "*" + std::to_string(this->mapSize.height)).c_str();
  std::cout << sizeMessage << std::endl;
  SDL_Log("%s", sizeMessage.c_str());
}

std::vector<std::vector<char>> DEAD_Map::getMapObjects() {
  return this->mapObjects;  
}
