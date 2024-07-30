#pragma once
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <vector>
#include <memory>
#include "../DEAD_map.h"

class DEAD_Renderer;

class DEAD_ParticleBase {
public:
  DEAD_ParticleBase(DEAD_Renderer* renderer);
  virtual ~DEAD_ParticleBase();
  virtual void play() = 0;
  virtual bool render() = 0;
protected:
  std::vector<SDL_Rect> particleTextureRects;
  SDL_Texture* particleTexture;
  DEAD_Renderer* renderer;
private:
};
