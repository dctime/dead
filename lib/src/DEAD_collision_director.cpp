#include "DEAD_player.h"
#include "hitbox/DEAD_circle_hitbox.h"
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

std::set<DEAD_MapObjectBase*> DEAD_CollisionDirector::entityCheckCollision(double targetX, double targetY, DEAD_Entity* entity) {
  std::vector<std::vector<int>> checkSequence = {{0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

  std::set<DEAD_MapObjectBase*> collideObjects;
  collideObjects.clear();

  for (std::vector<int> v : checkSequence) {
    int objectX = v[0] + (int)(targetX);
    int objectY = v[1] + (int)(targetY);

    
    if (objectX < 0 || objectX >= this->game->getMap()->getMapSize().width) continue;
    if (objectY < 0 || objectY >= this->game->getMap()->getMapSize().height) continue;


    DEAD_MapObjectBase* object = this->game->getMap()->getMapObjects()[objectY][objectX];
    if (!object->isPlayerCollidable()) {
      continue;
    }

    DEAD_Map::MapLocation futureLoc = {.x=targetX, .y=targetY};

    if (object->getHitBox()->isCollideWithCircle(futureLoc, entity->getHitbox()->getRadius())) {
      collideObjects.insert(object);
    }
  }
  
  return collideObjects;
}

std::set<DEAD_MapObjectBase*> DEAD_CollisionDirector::entityCheckCollision(DEAD_Entity* entity, DEAD_Map::MapLocation targetLoc) {
  return entityCheckCollision(targetLoc.x, targetLoc.y, entity);
}


std::set<DEAD_MapObjectBase*> DEAD_CollisionDirector::entityCheckCollision(DEAD_Entity* player, double moveXDelta, double moveYDelta) {

  DEAD_Map::MapLocation playerLoc = player->getPos();

  double targetX = player->getPos().x + moveXDelta;
  double targetY = player->getPos().y + moveYDelta;

  DEAD_Map::MapLocation futureLoc = player->getPos();
  futureLoc.x += moveXDelta;
  futureLoc.y += moveYDelta;

  return entityCheckCollision(player, futureLoc);
}

std::set<DEAD_MapObjectBase*> DEAD_CollisionDirector::bulletCheckCollision(DEAD_Bullet* bullet) {
  std::vector<std::vector<int>> checkSequence = {{0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

  std::set<DEAD_MapObjectBase*> collideObjects;
  collideObjects.clear();

  for (std::vector<int> v : checkSequence) {
    int objectX = v[0] + (int)(bullet->getLoc().x);
    int objectY = v[1] + (int)(bullet->getLoc().y);

    
    if (objectX < 0 || objectX >= this->game->getMap()->getMapSize().width) continue;
    if (objectY < 0 || objectY >= this->game->getMap()->getMapSize().height) continue;


    DEAD_MapObjectBase* object = this->game->getMap()->getMapObjects()[objectY][objectX];
    if (!object->isPlayerCollidable()) {
      continue;
    }

    if (object->getHitBox()->isCollideWithCircle(bullet->getLoc(), bullet->getBulletSize() / 2)) {
      collideObjects.insert(object);
    }
  }
  
  return collideObjects;
}





