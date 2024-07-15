#pragma once


#include "DEAD_player.h"
#include "map_objects/DEAD_map_object_base.h"


class DEAD_CollisionDirector {
public:
  DEAD_CollisionDirector(DEAD_Game* game);
  DEAD_MapObjectBase* playerCheckCollision(DEAD_Player* player);
private:
  DEAD_Game* game;

};
