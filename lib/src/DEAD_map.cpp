#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include "../include/DEAD_map.h"

DEAD_Map::DEAD_Map() {
  SDL_Log("Map Init");
}

DEAD_Map::~DEAD_Map() {
  SDL_Log("Map Destoryed");
}

void DEAD_Map::renderMap() {
  SDL_Log("Rendering Map");
}
