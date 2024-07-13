#include <DEAD_game.h>
#include <DEAD_pistol.h>
#include <SDL2/SDL_log.h>

DEAD_Pistol::DEAD_Pistol(DEAD_Player* player)
: DEAD_Guns(player) {}

SDL_Rect DEAD_Pistol::getTextureRect() {
  SDL_Rect rect = {.x=100, .y=0, .w=100, .h=100};
  return rect;
}
