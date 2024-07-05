#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include "../include/DEAD_map.h"

Map::Map() {
  SDL_Log("Map Init");
}

Map::~Map() {
  SDL_Log("Map Destoryed");
}

void Map::renderMap() {
  SDL_Log("Rendering Map");
}
