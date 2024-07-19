#pragma once

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <memory>
#include "DEAD_map.h"
#include "DEAD_renderer.h"
#include "DEAD_entity.h"
#include "DEAD_player.h"
#include "DEAD_controllable_player.h"
#include "DEAD_bullet_director.h"
#include "DEAD_collision_director.h"
#include "DEAD_item_drop_layer.h"

class DEAD_Game
  : public std::enable_shared_from_this<DEAD_Game> {
public:
  DEAD_Game(std::shared_ptr<DEAD_ControllablePlayer> player);
  ~DEAD_Game();
  void tick();
  void run();
  std::shared_ptr<DEAD_Map> getMap();
  std::shared_ptr<DEAD_Player> getPlayer();
  std::shared_ptr<DEAD_Renderer> getRenderer();
  std::shared_ptr<DEAD_BulletDirector> getBulletDirector();
  std::shared_ptr<DEAD_CollisionDirector> getCollisionDirector();
  std::shared_ptr<DEAD_ItemDropLayer> getItemDropLayer();
  const int SCREEN_WIDTH = 720;
  const int SCREEN_HEIGHT = 480;
private:
  SDL_Window* window;
  std::shared_ptr<DEAD_Map> map;
  std::shared_ptr<DEAD_ControllablePlayer> player;
  void eventHandle();
  bool running = true;
  std::shared_ptr<DEAD_Renderer> renderer;
  std::shared_ptr<DEAD_BulletDirector> bulletDirector;
  std::shared_ptr<DEAD_CollisionDirector> collisionDirector;
  std::shared_ptr<DEAD_ItemDropLayer> itemDropLayer;
};
