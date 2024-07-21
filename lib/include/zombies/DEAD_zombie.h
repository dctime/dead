#pragma once
#include "../DEAD_entity.h"

class DEAD_Zombie : public DEAD_Entity {
public:
  DEAD_Zombie(std::shared_ptr<DEAD_Game> game);
  SDL_Rect getTextureRect() override;
private:
};
