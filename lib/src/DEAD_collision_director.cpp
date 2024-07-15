#include <DEAD_collision_director.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <iostream>


DEAD_CollisionDirector::DEAD_CollisionDirector() {
  SDL_Log("collision init");
}

DEAD_MapObjectBase* DEAD_CollisionDirector::playerCheckCollision(DEAD_Player* player) {
  return nullptr;
}
