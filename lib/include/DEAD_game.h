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
#include "DEAD_decoration_layer.h"
#include "DEAD_decoration_layer_builder.h"
#include "DEAD_data_base_connector.h"

class DEAD_ControllablePlayer;

class DEAD_Game
  : public std::enable_shared_from_this<DEAD_Game> {
public:
  DEAD_Game(std::string playerName);
  ~DEAD_Game();
  void mapTick();
  void run();
  DEAD_Map* getMap();
  DEAD_Player* getPlayer();
  DEAD_Renderer* getRenderer();
  DEAD_BulletDirector* getBulletDirector();
  DEAD_CollisionDirector* getCollisionDirector();
  DEAD_ItemDropLayer* getItemDropLayer();
  DEAD_DecorationLayer* getDecorationLayer();
  DEAD_ZombieDirector* getZombieDirector();
  DEAD_SoundDirector* getSoundDirector();
  DEAD_DataBaseConnector* getDataBaseConnector();
  int getPassTicks();
  const int SCREEN_WIDTH = 720;
  const int SCREEN_HEIGHT = 480;

  static const int BULLET_COLLISION_DELAY;
  static const int MAIN_LOOP_DELAY;
private:
  SDL_Window* window;
  std::unique_ptr<DEAD_Map> map;
  std::unique_ptr<DEAD_ControllablePlayer> player;
  void eventHandle();
  bool running;
  bool ticking;
  std::unique_ptr<DEAD_Renderer> renderer;
  std::unique_ptr<DEAD_BulletDirector> bulletDirector;
  std::unique_ptr<DEAD_CollisionDirector> collisionDirector;
  std::unique_ptr<DEAD_ItemDropLayer> itemDropLayer;
  std::unique_ptr<DEAD_DecorationLayerBuilder> decorationLayerBuilder;
  std::unique_ptr<DEAD_DecorationLayer> decorationLayer;
  std::unique_ptr<DEAD_ZombieDirector> zombieDirector;
  std::unique_ptr<DEAD_SoundDirector> soundDirector;
  std::unique_ptr<DEAD_DataBaseConnector> dataBaseConnector;
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
  int passTicks;
  int lastTimeLoopTicks;
  
  friend class DEAD_GameBuilder;
};
