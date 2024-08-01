#include <SDL2/SDL_rect.h>
#include <map_objects/DEAD_cursed_dirt.h>

DEAD_CursedDirt::DEAD_CursedDirt(DEAD_Map::MapLocation loc)
  : DEAD_MapObjectBase(loc) {

}

char DEAD_CursedDirt::getChar() {
  return 'c';
}

SDL_Rect DEAD_CursedDirt::getTextureRect() {
  SDL_Rect rect = {.x=200, .y=0, .w=100, .h=100};
  return rect;
}
bool DEAD_CursedDirt::isPlayerCollidable() {
  return true;
}

bool DEAD_CursedDirt::isZombieCollidable() {
  return false;
}
