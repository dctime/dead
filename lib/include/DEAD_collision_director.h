#pragma once

#include "DEAD_player.h"
#include "bullets/DEAD_bullet.h"
#include "map_objects/DEAD_map_object_base.h"
#include "zombies/DEAD_zombie.h"
#include <memory>
#include <set>

class DEAD_CollisionDirector {
public:
  DEAD_CollisionDirector(DEAD_Game* game);

  std::set<DEAD_MapObjectBase*>
  entityCheckCollision(DEAD_Entity* entity,
                       double deltaX, double deltaY);
  std::set<DEAD_MapObjectBase*>
  entityCheckCollision(double targetX, double targetY,
                       DEAD_Entity* entity);
  std::set<DEAD_MapObjectBase*>
  entityCheckCollision(DEAD_Entity* entity,
                       DEAD_Map::MapLocation targetLoc);

  std::set<DEAD_MapObjectBase*>
  playerCheckCollision(double targetX, double targetY,
                       DEAD_Player* player);

  std::set<DEAD_MapObjectBase*>
  playerCheckCollision(DEAD_Player* player,
                       DEAD_Map::MapLocation targetLoc);
  std::set<DEAD_MapObjectBase*>
  playerCheckCollision(DEAD_Player* player,
                       double deltaX, double deltaY);
  std::set<DEAD_MapObjectBase*>
  bulletCheckCollision(DEAD_Bullet* bullet);

  DEAD_Zombie* bulletCheckCollideZombie(DEAD_Bullet* bullet);

private:
  DEAD_Game* game;
};
