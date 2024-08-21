#include "DEAD_player.h"
#include "guns/DEAD_gun.h"
#include <SDL2/SDL_rect.h>
#include <guns/DEAD_shotgun.h>
#include <memory>

DEAD_Shotgun::DEAD_Shotgun(DEAD_Player* player)
  : DEAD_Gun(player, 5, 5000, 5000) {

}
DEAD_Shotgun::~DEAD_Shotgun() {}
SDL_Rect DEAD_Shotgun::getTextureRect() {
  SDL_Rect rect = {.x=200, .y=0, .w=100, .h=100};
  return rect;
}


SDL_Rect DEAD_Shotgun::getItemTextureRect() {
  SDL_Rect rect = {.x=100, .y=0, .w=100, .h=100};
  return rect;
}

std::string DEAD_Shotgun::getName() {
  return "Shotgun";
}

std::string DEAD_Shotgun::getNote() {
  return "Not Implemented yet";
}
