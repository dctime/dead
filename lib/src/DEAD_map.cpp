#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <cstdio>
#include <fstream>
#include <string>
#include <iostream>
#include "../include/DEAD_map.h"

DEAD_Map::DEAD_Map() {
  SDL_Log("Map Init");
  this->loadMap("awad");
}

DEAD_Map::~DEAD_Map() {
  SDL_Log("Map Destoryed");
}

void DEAD_Map::renderMap() {
  SDL_Log("Rendering Map");
}

void DEAD_Map::loadMap(const char* filePath) {
  std::ifstream inputFile(filePath);
  std::string line;

  while (getline(inputFile, line)) {
    std::cout << line << std::endl;
  }

  inputFile.close();
}
