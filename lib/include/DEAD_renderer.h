#pragma once

#include "DEAD_item_drop.h"
#include <SDL2/SDL_render.h>
#include <memory>
#include <string>
#include "DEAD_entity.h"
#include "DEAD_zombie_director.h"

class DEAD_Game;
class DEAD_Player;
class DEAD_Bullet;

struct RenderAnchor {
    double x;
    double y;
};

struct ScreenLocation {
  int x;
  int y;
};

class DEAD_RectLocMapObjects {
public:
  static const SDL_Rect STONE;
  static const SDL_Rect WOOD;
};

class DEAD_Renderer {
public:
  DEAD_Renderer(SDL_Window* window, std::shared_ptr<DEAD_Game> game);
  ~DEAD_Renderer();
  void render();
  void moveRenderAnchor(double x, double y);
  ScreenLocation getEntityRenderLocation(std::shared_ptr<DEAD_Entity> entity, bool mid);
  ScreenLocation getBulletRenderLocation(std::shared_ptr<DEAD_Bullet> bullet);
  ScreenLocation getPointRenderLocation(double x, double y);
private:
  void renderMapObjects();
  SDL_Renderer* renderer;
  int renderBlockSize;
  std::shared_ptr<DEAD_Game> game;
  RenderAnchor renderAnchor = {.x=0, .y=0};
  SDL_Rect renderRect = {.x=0, .y=0, .w=renderBlockSize, .h=renderBlockSize};
  SDL_Texture *mapObjectTexture;
  SDL_Texture *playerTexture;
  SDL_Texture *bulletTexture;
  SDL_Texture* itemTexture;
  SDL_Texture* zombiesTexture;
  void renderPlayer(std::shared_ptr<DEAD_Player> player);
  void renderZombies(const std::shared_ptr<DEAD_ZombieDirector>& zombieDirector);
  void renderEntity(std::shared_ptr<DEAD_Entity> entity, SDL_Texture* texture);
  void renderItemDropLayer();
  void renderBullets();
  void drawZombieMovementMap();
  void getTextureFromSurface(SDL_Texture*& texture, std::string filePath);
  ScreenLocation getItemDropRenderLocation(std::shared_ptr<DEAD_ItemDrop> itemDrop);
};
