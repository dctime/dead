#include "decorations/DEAD_decoration_base.h"
#include "subrenderers/DEAD_subrenderer_base.h"
#include <SDL2/SDL_render.h>
#include <subrenderers/DEAD_decoration_renderer.h>
#include <DEAD_renderer.h>
#include <DEAD_filepaths.h>
#include <SDL2/SDL_image.h>

DEAD_DecorationRenderer::DEAD_DecorationRenderer(DEAD_Renderer* renderer, DEAD_DecorationLayer* layer)
  : DEAD_SubRendererBase(renderer), layer(layer) {
  SDL_Surface *textureSurface = IMG_Load(DEAD_FilePaths::DECORATION_TEXTURE_PNG.c_str());
  this->decorationTexture = SDL_CreateTextureFromSurface(renderer->getSDLRenderer(), textureSurface);
  SDL_FreeSurface(textureSurface);
}

DEAD_DecorationRenderer::~DEAD_DecorationRenderer() {
  SDL_DestroyTexture(this->decorationTexture);  
}

void DEAD_DecorationRenderer::render() {
  for (const std::unique_ptr<DEAD_DecorationBase>& deco : layer->getDecorations()) {
    ScreenLocation renderLoc = this->getDecorationRenderLocation(deco.get());
    SDL_Rect renderRect = {.x=renderLoc.x, .y=renderLoc.y,
                          .w=(int)(deco->getWidth()*this->renderer->getRenderBlockSize()), .h=(int)(deco->getHeight()*this->renderer->getRenderBlockSize())};
    
    SDL_Rect textureRect = deco->getTextureRect();
    SDL_RenderCopy(this->renderer->getSDLRenderer(), this->decorationTexture, &textureRect, &renderRect);
  }
}

ScreenLocation DEAD_DecorationRenderer::getDecorationRenderLocation(DEAD_DecorationBase* deco) {
  ScreenLocation loc;
  loc = this->renderer->getPointRenderLocation(deco->getLoc().x - deco->getWidth()/2, deco->getLoc().y - deco->getHeight()/2);
  return loc;
}
