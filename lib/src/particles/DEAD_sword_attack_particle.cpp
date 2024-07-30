#include "DEAD_map.h"
#include "DEAD_renderer.h"
#include "particles/DEAD_particle_base.h"
#include <DEAD_game.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <climits>
#include <memory>
#include <particles/DEAD_sword_attack_particle.h>
#include <vector>

DEAD_SwordAttackParticle::DEAD_SwordAttackParticle(
    DEAD_Renderer* renderer, DEAD_Map::MapLocation loc,
    double angle)
    : DEAD_ParticleBase(renderer), TICKS_LENGTH(300), startTicks(INT_MIN),
      angle(angle), loc(loc) {
  SDL_Rect rectStartSwordTextureRect = {.x = 0, .y = 0, .w = 100, .h = 100};
  SDL_Rect rectMidSwordTextureRect = {.x = 100, .y = 0, .w = 100, .h = 100};
  SDL_Rect rectEndSwordTextureRect = {.x = 200, .y = 0, .w = 100, .h = 100};

  this->particleTextureRects.push_back(rectStartSwordTextureRect);
  this->particleTextureRects.push_back(rectMidSwordTextureRect);
  this->particleTextureRects.push_back(rectEndSwordTextureRect);

  this->targetRenderRect.w = renderer->getRenderBlockSize();
  this->targetRenderRect.h = renderer->getRenderBlockSize();
  ScreenLocation leftUpScreenLoc = renderer->getPointRenderLocation(loc.x, loc.y);
  this->targetRenderRect.x = leftUpScreenLoc.x - (int)(renderer->getRenderBlockSize() / 2);
  this->targetRenderRect.y = leftUpScreenLoc.y - (int)(renderer->getRenderBlockSize() / 2);
}

void DEAD_SwordAttackParticle::play() { this->startTicks = SDL_GetTicks64(); }

bool DEAD_SwordAttackParticle::render() {
  int renderingSeconds = SDL_GetTicks64() - this->startTicks;
  if (renderingSeconds >= this->TICKS_LENGTH)
    return false;

  SDL_Rect *renderingTextureRect;

  if (renderingSeconds < this->TICKS_LENGTH / 3) {
    renderingTextureRect = &this->particleTextureRects.at(0);
  } else if (this->TICKS_LENGTH / 3 <= renderingSeconds &&
             renderingSeconds < this->TICKS_LENGTH / 3 * 2) {
    renderingTextureRect = &this->particleTextureRects.at(1);
  } else if (this->TICKS_LENGTH / 3 * 2 <= renderingSeconds &&
             renderingSeconds < this->TICKS_LENGTH) {
    renderingTextureRect = &this->particleTextureRects.at(2);
  }

  SDL_RenderCopyEx(this->renderer->getSDLRenderer(), this->particleTexture,
                   renderingTextureRect, &this->targetRenderRect, angle, NULL,
                   SDL_RendererFlip::SDL_FLIP_NONE);
  return true;
}
