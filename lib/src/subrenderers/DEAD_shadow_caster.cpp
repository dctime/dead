#include "SDL_pixels.h"
#include "SDL_surface.h"
#include "labels/DEAD_label_base.h"
#include "subrenderers/DEAD_subrenderer_base.h"
#include <DEAD_game.h>
#include <DEAD_renderer.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_render.h>
#include <SDL2_gfxPrimitives.h>
#include <labels/DEAD_point_label.h>
#include <memory>
#include <subrenderers/DEAD_shadow_caster.h>

DEAD_ShadowCaster::DEAD_ShadowCaster(DEAD_Renderer *renderer)
    : DEAD_SubRendererBase(renderer), map(renderer->getGame()->getMap()),
      labelRenderer(std::make_unique<DEAD_LabelRenderer>(renderer)) {}

void DEAD_ShadowCaster::render() {
  ScreenLocation testLoc = this->renderer->getPointRenderLocation(1, 1);
  std::unique_ptr<DEAD_LabelBase> testPoint =
      std::make_unique<DEAD_PointLabel>(3, 28, 0.3, this->renderer);
  this->labelRenderer->addLabel(testPoint);
  this->labelRenderer->render();
  // make a square mask

  SDL_BlendMode whiteToMask = SDL_ComposeCustomBlendMode(
      SDL_BLENDFACTOR_ONE, SDL_BLENDFACTOR_ZERO, SDL_BLENDOPERATION_ADD,
      SDL_BLENDFACTOR_ONE_MINUS_DST_ALPHA, SDL_BLENDFACTOR_ZERO,
      SDL_BLENDOPERATION_ADD);

  SDL_Texture *shadowMask = SDL_CreateTexture(
      this->renderer->getSDLRenderer(), SDL_PIXELFORMAT_RGBA8888,
      SDL_TEXTUREACCESS_TARGET, this->renderer->getGame()->SCREEN_WIDTH,
      this->renderer->getGame()->SCREEN_HEIGHT);

  SDL_SetRenderTarget(this->renderer->getSDLRenderer(), shadowMask);
  Sint16 polygonX[] = {300, 600, 600, 300};
  Sint16 polygonY[] = {300, 300, 600, 600};

  // only alpha matters color doesnt matter
  filledPolygonRGBA(this->renderer->getSDLRenderer(), polygonX, polygonY, 4,
                    255, 255, 255, 255);
  

  // draw full screen black with mask blendmode
  SDL_SetRenderDrawBlendMode(this->renderer->getSDLRenderer(),
                             whiteToMask);

  // r,g,b => mask color a=>shadow strength
  int shadowStrength = 255;
  SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), 0, 0, 0, shadowStrength);
  SDL_RenderFillRect(this->renderer->getSDLRenderer(), NULL);
  SDL_SetRenderDrawBlendMode(this->renderer->getSDLRenderer(), SDL_BLENDMODE_BLEND);

  SDL_SetRenderTarget(this->renderer->getSDLRenderer(), NULL);
  SDL_SetTextureBlendMode(shadowMask, SDL_BLENDMODE_BLEND);
  SDL_RenderCopy(this->renderer->getSDLRenderer(), shadowMask, NULL, NULL);
  // find all points sorted in angle
  // find all edges
  // find a way to render a polygon mask
  // complete all stuff
}
