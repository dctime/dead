#pragma once

#include "DEAD_player.h"
#include <SDL2/SDL.h>
#include <memory>

class DEAD_Bullet : std::enable_shared_from_this<DEAD_Bullet> {
public:
  DEAD_Bullet(DEAD_Player* owner);
  virtual SDL_Rect getBulletTextureRect() = 0;
  DEAD_Player* getOwner();
  virtual void registerBullet() = 0;
private:
  DEAD_Player* owner;
  DEAD_Player::Position pos;
};
