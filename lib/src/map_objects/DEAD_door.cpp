#include <SDL2/SDL_log.h>
#include <SDL2/SDL_rect.h>
#include <map_objects/DEAD_door.h>
#include <SDL2/SDL.h>

DEAD_Door::DEAD_Door(DEAD_Map::MapLocation loc) 
  : DEAD_MultitextureObjectBase(loc), isOpen(false) {
  this->closedTextureRects.push_back({.x=100, .y=100, .w=100, .h=100});
  this->closedTextureRects.push_back({.x=200, .y=100, .w=100, .h=100});
  this->closedTextureRects.push_back({.x=300, .y=100, .w=100, .h=100});
  this->openTextureRects.push_back({.x=400, .y=100, .w=100, .h=100});
  this->openTextureRects.push_back({.x=0, .y=200, .w=100, .h=100});
}

char DEAD_Door::getChar() { return 'd'; }
bool DEAD_Door::isPlayerCollidable() {
  if (isOpen) return false;
  return true; 
}
bool DEAD_Door::isZombieCollidable() { return false; }

std::vector<SDL_Rect> DEAD_Door::getTextureRects() {
  if (isOpen) return this->openTextureRects; 
  return this->closedTextureRects;
}
