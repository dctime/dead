#pragma once
#include <SDL2/SDL_video.h>
#include "DEAD_renderer.h"
#include <iostream>

class DEAD_Game;

class DEAD_Renderer3D {
public:
  DEAD_Renderer3D(SDL_Window* window, DEAD_Renderer* renderer, DEAD_Game* game); 
  ~DEAD_Renderer3D();
  void render();
  void renderMinimap();
  void renderFirstLayer();
  
  Uint32 getPixelFromSurface(SDL_Surface* surface, int x, int y); 
  void getPixelInfoFromRectAndXYWithScale(int &r, int &g, int &b, int &a, int x, int y, const SDL_Rect& rect, double scale);

private:
  SDL_Window* window;
  DEAD_Renderer* renderer;
  DEAD_Game* game;
  int minimapWidth;
  int minimapHeight;
  SDL_Texture* minimapTexture;
  int horizontalFOV;
  double heightForHalfFullInOneMapBlock;
  double maxRenderDistance;
  SDL_Texture* playerViewLayerTexture;
  double blockRenderHeight;

  SDL_Surface* zombie3DSurface;


  SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

  double getAngleFromRenderX(int x);
  int getRenderXFromAngle(double angle);


  struct XToDistance {
    int x;
    double distance;
    bool isZombie = false;
    SDL_Rect zombieRenderRect;
  };

  

  static bool sortByDistance(const XToDistance& data1, const XToDistance& data2);
};
