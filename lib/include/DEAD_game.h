#pragma once

#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <memory>
#include "DEAD_map.h"
#include "DEAD_renderer.h"
#include "DEAD_entity.h"
#include "DEAD_player.h"
#include "DEAD_bullet_director.h"
#include "DEAD_collision_director.h"
#include "DEAD_item_drop_layer.h"
#include "DEAD_zombie_director.h"
#include "DEAD_sound_director.h"

class DEAD_ControllablePlayer;

class DEAD_Game
  : public std::enable_shared_from_this<DEAD_Game> {
public:
  DEAD_Game();
  ~DEAD_Game();
  void mapTick();
  void run();
  std::shared_ptr<DEAD_Map> getMap();
  std::shared_ptr<DEAD_Player> getPlayer();
  void setPlayer(std::shared_ptr<DEAD_ControllablePlayer> player);
  std::shared_ptr<DEAD_Renderer> getRenderer();
  std::shared_ptr<DEAD_BulletDirector> getBulletDirector();
  std::shared_ptr<DEAD_CollisionDirector> getCollisionDirector();
  std::shared_ptr<DEAD_ItemDropLayer> getItemDropLayer();
  std::shared_ptr<DEAD_ZombieDirector> getZombieDirector();
  std::shared_ptr<DEAD_SoundDirector> getSoundDirector();
  const int SCREEN_WIDTH = 720;
  const int SCREEN_HEIGHT = 480;

  static const int BULLET_COLLISION_DELAY;
  static const int MAIN_LOOP_DELAY;
private:
  SDL_Window* window;
  std::shared_ptr<DEAD_Map> map;
  std::shared_ptr<DEAD_ControllablePlayer> player;
  void eventHandle();
  bool running;
  bool ticking;
  std::shared_ptr<DEAD_Renderer> renderer;
  std::shared_ptr<DEAD_BulletDirector> bulletDirector;
  std::shared_ptr<DEAD_CollisionDirector> collisionDirector;
  std::shared_ptr<DEAD_ItemDropLayer> itemDropLayer;
  std::shared_ptr<DEAD_ZombieDirector> zombieDirector;
  std::shared_ptr<DEAD_SoundDirector> soundDirector;
  void initObjectThatHasSharedFromThis();
  SDL_TimerID bulletCollisionID;
  SDL_TimerID mainLoopID;
  SDL_TimerID zombieSpawnID;
  int getSecretNumber();
  void checkPlayerDied();
  static Uint32 bulletCheckCollisionCallback(Uint32 interval, void *param);
  static Uint32 playerMovementCallback(Uint32 interval, void *param);
  static Uint32 spawnZombieCallback(Uint32 interval, void *param);
  static void checkAndDeleteCollisionBullets(DEAD_Game* game);
  static void mainLoop(DEAD_Game* game);
  static void zombieSpawn(DEAD_Game* game);
  
  friend class DEAD_GameBuilder;
};
