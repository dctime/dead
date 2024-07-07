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

void DEAD_Map::renderMap() {
  SDL_Log("Rendering Map");
}

void DEAD_Map::loadMap() {
  mapObjects.clear();
  const char* inputFilePath = DEAD_FilePaths::MAP_FILE_PATH.c_str();
  std::ifstream inputFile(inputFilePath);
  std::string line;

  while (getline(inputFile, line)) {
    std::vector<char> temp;
    for (char c : line) {
      temp.push_back(c);
    }
    mapObjects.push_back(temp);

  }
  
  int width = -1;
  for (std::vector<char> v : mapObjects) {
    if (width < (int) v.size()) { width = v.size(); }
    for (char c : v) {
      std::cout << c;
    }
    std::cout << std::endl;
  }
  int height = mapObjects.size();
  
  std::string sizeMessage = 
    ("Map Size: " + std::to_string(width) + "*" + std::to_string(height)).c_str();
  std::cout << sizeMessage << std::endl;
  SDL_Log("%s", sizeMessage.c_str());
  inputFile.close();
}
