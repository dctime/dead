#include "map_objects/DEAD_map_object_base.h"
#include <DEAD_collision_director.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <DEAD_game.h>
#include <iostream>
DEAD_CollisionDirector::DEAD_CollisionDirector(DEAD_Game* game) 
  : game(game) {
  SDL_Log("collision init");
}

DEAD_MapObjectBase* DEAD_CollisionDirector::playerCheckCollision(DEAD_Player* player) {
  DEAD_Map::MapLocation playerLoc = *(player->getPos());
  // FIXME: heading to add player size and rendering stuff
  std::cout << "Send Request to collision director" << std::endl;
  return nullptr;
}
