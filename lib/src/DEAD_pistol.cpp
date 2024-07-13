#include "DEAD_player.h"
#include <DEAD_game.h>
#include <SDL2/SDL_log.h>
#include <algorithm>
#include <iostream>
#include <string>

DEAD_Pistol::DEAD_Pistol() {
  SDL_Log("Pistol Created");
}
DEAD_Pistol::~DEAD_Pistol() {
  SDL_Log("Pistol Destoryed");
}

SDL_Rect DEAD_Pistol::getTextureRect() {
  SDL_Rect rect = {.x=100, .y=0, .w=100, .h=100};
  return rect;
}
