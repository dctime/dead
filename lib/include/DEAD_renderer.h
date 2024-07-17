#pragma once

#include <SDL2/SDL_render.h>

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
  DEAD_Renderer(SDL_Window* window, DEAD_Game* game);
  ~DEAD_Renderer();
  void render();
  void moveRenderAnchor(double x, double y);
  ScreenLocation getPlayerRenderLocation(DEAD_Player* player, bool mid);
  ScreenLocation getBulletRenderLocation(DEAD_Bullet* bullet);
private:
  void renderMapObjects();
  SDL_Renderer* renderer;
  int renderBlockSize;
  DEAD_Game* game;
  RenderAnchor renderAnchor = {.x=0, .y=0};
  SDL_Rect renderRect = {.x=0, .y=0, .w=renderBlockSize, .h=renderBlockSize};
  SDL_Texture *mapObjectTexture;
  SDL_Texture *playerTexture;
  SDL_Texture *bulletTexture;
  void renderPlayer(DEAD_Player* player);
  void renderBullets();
};
