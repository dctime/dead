#pragma once

#include "DEAD_item_drop.h"
#include <SDL2/SDL_render.h>
#include <memory>
#include <string>
#include "DEAD_entity.h"
#include "DEAD_zombie_director.h"
#include "subrenderers/DEAD_ui_renderer.h"
#include "subrenderers/DEAD_particle_renderer.h"

class DEAD_Game;
class DEAD_Player;
class DEAD_Bullet;
class DEAD_PlayerInventoryRenderer;

struct RenderAnchor {
    double x;
    double y;
};

struct ScreenLocation {
  int x;
  int y;
};

struct DEAD_ScreenLocationFromLeftDown {
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
  DEAD_Renderer(SDL_Window* window, DEAD_Game* game);
  ~DEAD_Renderer();
  void render();
  void moveRenderAnchor(double x, double y);
  ScreenLocation getEntityRenderLocation(DEAD_Entity* entity, bool mid);
  ScreenLocation getBulletRenderLocation(DEAD_Bullet* bullet);
  ScreenLocation getPointRenderLocation(double x, double y);
  DEAD_ParticleRenderer* getParticleRenderer();
  SDL_Renderer* getSDLRenderer();
  int getRenderBlockSize();
  void initWithSharedFromThis(DEAD_Renderer* renderer);
  void startYouDied();
  void closeYouDied();
  DEAD_Game* getGame();
private:
  void renderMapObjects();
  SDL_Renderer* renderer;
  std::unique_ptr<DEAD_UIRenderer> uiRenderer;
  std::unique_ptr<DEAD_ParticleRenderer> particleRenderer;
  std::unique_ptr<DEAD_PlayerInventoryRenderer> playerInventoryRenderer;
  int renderBlockSize;
  DEAD_Game* game;
  RenderAnchor renderAnchor = {.x=0, .y=0};
  SDL_Rect renderRect = {.x=0, .y=0, .w=renderBlockSize, .h=renderBlockSize};
  SDL_Texture *mapObjectTexture;
  SDL_Texture *playerTexture;
  SDL_Texture *bulletTexture;
  SDL_Texture* itemTexture;
  SDL_Texture* zombiesTexture;
  SDL_Texture* youDiedFontTexture;
  void renderPlayer(DEAD_Player* player);
  void renderZombies(DEAD_ZombieDirector* zombieDirector);
  void renderEntity(DEAD_Entity* entity, SDL_Texture* texture);
  void renderItemDropLayer();
  void renderBullets();
  void renderYouDied();
  void drawZombieMovementMap();
  void getTextureFromSurface(SDL_Texture*& texture, std::string filePath);
  void getTextureFromFont(std::string fontFilePath, SDL_Texture*& texture, std::string text, int fontSize, SDL_Color color);
  ScreenLocation getItemDropRenderLocation(const std::shared_ptr<DEAD_ItemDrop>& itemDrop);
  int youDiedAlpha;
  bool playingYouDied;
  int startYouDiedTicks;
};
