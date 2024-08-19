#include "map_objects/DEAD_map_object_base.h"
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_rect.h>
#include <map_objects/DEAD_wood.h>
#include <SDL2/SDL.h>
DEAD_Wood::DEAD_Wood(DEAD_Map::MapLocation loc) 
  : DEAD_MapObjectBase(loc), visible(false) {
  
}

char DEAD_Wood::getChar() { return 'w'; }
bool DEAD_Wood::isPlayerCollidable() { return true; }
bool DEAD_Wood::isZombieCollidable() { return true; }
SDL_Rect DEAD_Wood::getTextureRect() {
  SDL_Rect rect = {.x = 100, .y = 0, .w = 100, .h = 100};
  return rect;
}

bool DEAD_Wood::isVisible() {
  return this->visible; 
}

void DEAD_Wood::setToVisible() {
  this->visible = true; 
}


