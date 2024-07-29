#pragma once
#include "../DEAD_entity.h"
#include "../DEAD_zombie_movement_maps.h"

class DEAD_Zombie : public DEAD_Entity {
public:
  DEAD_Zombie(std::shared_ptr<DEAD_Game> game);
  SDL_Rect getTextureRect() override;
  int getAttackDamage();
  bool attackReady();
  void bite(std::shared_ptr<DEAD_Player> player);
  ZombieVector getMovingUnitVector();
  void setMovingUnitVector(ZombieVector vector);
private:
  int lastTimeAttackTicks;
  int attackCoolDown;
  ZombieVector movingUnitVector;
};
