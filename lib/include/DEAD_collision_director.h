#pragma once


#include "DEAD_player.h"
#include "map_objects/DEAD_map_object_base.h"
#include "bullets/DEAD_bullet.h" 
#include <memory>
#include <set>



class DEAD_CollisionDirector {
public:
  DEAD_CollisionDirector(std::shared_ptr<DEAD_Game> game);

  std::set<std::shared_ptr<DEAD_MapObjectBase>> entityCheckCollision(const std::shared_ptr<DEAD_Entity>& entity, double deltaX, double deltaY);
  std::set<std::shared_ptr<DEAD_MapObjectBase>> entityCheckCollision(double targetX, double targetY, const std::shared_ptr<DEAD_Entity>& entity);
  std::set<std::shared_ptr<DEAD_MapObjectBase>> entityCheckCollision(const std::shared_ptr<DEAD_Entity>& entity, DEAD_Map::MapLocation targetLoc);

  std::set<std::shared_ptr<DEAD_MapObjectBase>> bulletCheckCollision(const std::shared_ptr<DEAD_Bullet>& bullet);

private:
  std::shared_ptr<DEAD_Game> game;

};
