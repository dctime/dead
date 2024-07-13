#include <DEAD_game.h>
#include <SDL2/SDL_log.h>
#include <algorithm>
#include <iostream>

DEAD_Pistol::DEAD_Pistol():DEAD_Weapon() {
  SDL_Log("Pistol Created");
}
DEAD_Pistol::~DEAD_Pistol() {
  SDL_Log("Pistol Destoryed");
}
