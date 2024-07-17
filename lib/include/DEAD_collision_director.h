#pragma once


#include "DEAD_player.h"
#include "map_objects/DEAD_map_object_base.h"
#include "DEAD_bullet.h" 
#include <set>



class DEAD_CollisionDirector {
public:
  DEAD_CollisionDirector(DEAD_Game* game);
  std::set<DEAD_MapObjectBase*> playerCheckCollision(DEAD_Player* player, double x, double y);
  std::set<DEAD_MapObjectBase*> playerCheckCollision(double targetX, double targetY, DEAD_Player* player);
  std::set<DEAD_MapObjectBase*> playerCheckCollision(DEAD_Player* player, DEAD_Map::MapLocation targetLoc);

  std::set<DEAD_MapObjectBase*> bulletCheckCollision(DEAD_Bullet* bullet);
private:
  DEAD_Game* game;

};
