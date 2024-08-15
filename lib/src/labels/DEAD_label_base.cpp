#include "DEAD_filepaths.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <labels/DEAD_label_base.h>
#include <DEAD_renderer.h>

DEAD_LabelBase::DEAD_LabelBase(double mapX, double mapY, DEAD_Renderer* renderer)
  : renderer(renderer) {
  this->midLoc = {.x=mapX, .y=mapY};
  SDL_Surface *textureSurface = IMG_Load(DEAD_FilePaths::LABEL_TEXTURE_PNG.c_str());
  this->labelTexture = SDL_CreateTextureFromSurface(renderer->getSDLRenderer(), textureSurface);
  SDL_FreeSurface(textureSurface);
}

DEAD_LabelBase::~DEAD_LabelBase() {
  SDL_DestroyTexture(this->labelTexture);
}

DEAD_Renderer* DEAD_LabelBase::getRenderer() {
  return this->renderer;
}

SDL_Texture* DEAD_LabelBase::getLabelTexture() {
  return this->labelTexture; 
}

DEAD_Map::MapLocation DEAD_LabelBase::getMidLoc() {
  return this->midLoc;
}

