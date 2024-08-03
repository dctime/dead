#include "DEAD_filepaths.h"
#include <SDL2/SDL_image.h>
#include <memory>
#include <particles/DEAD_particle_base.h>
#include <DEAD_renderer.h>
#include <SDL2/SDL_render.h>

DEAD_ParticleBase::~DEAD_ParticleBase() {
  SDL_DestroyTexture(this->particleTexture); 
}

DEAD_ParticleBase::DEAD_ParticleBase(DEAD_Renderer* renderer)
  : renderer(renderer) {
  SDL_Surface *textureSurface = IMG_Load(DEAD_FilePaths::PARTICLE_TEXTURE_PNG.c_str());
  this->particleTexture = SDL_CreateTextureFromSurface(renderer->getSDLRenderer(), textureSurface);
  SDL_FreeSurface(textureSurface);
   
}

