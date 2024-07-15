#pragma once


#include "DEAD_player.h"
#include "map_objects/DEAD_map_object_base.h"
#include <set>


class DEAD_CollisionDirector {
public:
  DEAD_CollisionDirector(DEAD_Game* game);
  std::set<DEAD_MapObjectBase*> playerCheckCollision(DEAD_Player* player, double x, double y);
private:
  DEAD_Game* game;

};
