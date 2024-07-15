#include "map_objects/DEAD_map_object_base.h"
#include <DEAD_collision_director.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <DEAD_game.h>
#include <iostream>
#include <vector>
DEAD_CollisionDirector::DEAD_CollisionDirector(DEAD_Game* game) 
  : game(game) {
  SDL_Log("collision init");
}

std::set<DEAD_MapObjectBase*> DEAD_CollisionDirector::playerCheckCollision(DEAD_Player* player, double moveXDelta, double moveYDelta) {
  std::set<DEAD_MapObjectBase*> collideObjects;
  collideObjects.clear();

  DEAD_Map::MapLocation playerLoc = *(player->getPos());

  double targetX = player->getPos()->x + moveXDelta;
  double targetY = player->getPos()->y + moveYDelta;
  double playerSize = player->getSize();

  std::vector<std::vector<int>> checkSequence = {{0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1}};


  for (std::vector<int> v : checkSequence) {
    int objectX = v[0] + (int)(targetX);
    int objectY = v[1] + (int)(targetY);

    
    if (objectX < 0 || objectX >= this->game->getMap()->getMapSize().width) continue;
    if (objectY < 0 || objectY >= this->game->getMap()->getMapSize().height) continue;


    DEAD_MapObjectBase* object = this->game->getMap()->getMapObjects()[objectY][objectX];
    if (!object->isPlayerCollidable()) {
      continue;
    }
   

    if (object->getHitBox()->isCollideWithCircle(player->getHitbox())) {
      collideObjects.insert(object);
    }
  }
  
  if (collideObjects.size() > 0) std::cout << "Collide!!!!" << std::endl;
  return collideObjects;
}
