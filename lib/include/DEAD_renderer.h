#pragma once

#include "DEAD_item_drop.h"
#include <SDL2/SDL_render.h>
#include <memory>
#include <string>
#include "DEAD_entity.h"
#include "DEAD_zombie_director.h"
#include "DEAD_ui_renderer.h"
#include "DEAD_particle_renderer.h"

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
  std::shared_ptr<DEAD_ParticleRenderer> getParticleRenderer();
  SDL_Renderer* getSDLRenderer();
  int getRenderBlockSize();
  void initWithSharedFromThis(std::shared_ptr<DEAD_Renderer> renderer);
  void startYouDied();
  void closeYouDied();
  std::shared_ptr<DEAD_Game> getGame();
private:
  void renderMapObjects();
  SDL_Renderer* renderer;
  std::shared_ptr<DEAD_UIRenderer> uiRenderer;
  std::shared_ptr<DEAD_ParticleRenderer> particleRenderer;
  int renderBlockSize;
  std::shared_ptr<DEAD_Game> game;
  RenderAnchor renderAnchor = {.x=0, .y=0};
  SDL_Rect renderRect = {.x=0, .y=0, .w=renderBlockSize, .h=renderBlockSize};
  SDL_Texture *mapObjectTexture;
  SDL_Texture *playerTexture;
  SDL_Texture *bulletTexture;
  SDL_Texture* itemTexture;
  SDL_Texture* zombiesTexture;
  SDL_Texture* youDiedFontTexture;
  void renderPlayer(std::shared_ptr<DEAD_Player> player);
  void renderZombies(const std::shared_ptr<DEAD_ZombieDirector>& zombieDirector);
  void renderEntity(std::shared_ptr<DEAD_Entity> entity, SDL_Texture* texture);
  void renderItemDropLayer();
  void renderBullets();
  void renderYouDied();
  void drawZombieMovementMap();
  void getTextureFromSurface(SDL_Texture*& texture, std::string filePath);
  void getTextureFromFont(std::string fontFilePath, SDL_Texture*& texture, std::string text, int fontSize, SDL_Color color);
  ScreenLocation getItemDropRenderLocation(std::shared_ptr<DEAD_ItemDrop> itemDrop);
  int youDiedAlpha;
  bool playingYouDied;
  int startYouDiedTicks;
};
