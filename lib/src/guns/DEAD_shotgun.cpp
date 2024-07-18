#include <guns/DEAD_shotgun.h>

DEAD_Shotgun::DEAD_Shotgun() {}
DEAD_Shotgun::~DEAD_Shotgun() {}
SDL_Rect DEAD_Shotgun::getTextureRect() {
  SDL_Rect rect = {.x=200, .y=0, .w=100, .h=100};
  return rect;
}
