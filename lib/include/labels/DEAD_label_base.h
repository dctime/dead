#pragma once
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include "../DEAD_map.h"
#include "../DEAD_renderer.h"

class DEAD_LabelBase {
public:
  DEAD_LabelBase(double mapX, double mapY, DEAD_Renderer* renderer);
  virtual ~DEAD_LabelBase();
  virtual void render() = 0;
  DEAD_Map::MapLocation getMidLoc();
  DEAD_Renderer* getRenderer();
  SDL_Texture* getLabelTexture();

private:
  DEAD_Map::MapLocation midLoc;
  SDL_Texture* labelTexture;
  DEAD_Renderer* renderer;
};
