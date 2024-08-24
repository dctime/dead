#include "DEAD_functions.h"
#include "subrenderers/DEAD_decoration_renderer.h"
#include <DEAD_controllable_player.h>
#include <DEAD_game.h>
#include <DEAD_renderer.h>
#include <DEAD_renderer3d.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <subrenderers/DEAD_explainer.h>
#include <subrenderers/DEAD_player_inventory_renderer.h>
#include <subrenderers/DEAD_shadow_caster.h>
#include <subrenderers/DEAD_ui_renderer.h>

DEAD_Renderer3D::DEAD_Renderer3D(SDL_Window *window, DEAD_Renderer *renderer,
                                 DEAD_Game *game)
    : window(window), renderer(renderer), game(game), minimapWidth(324),
      minimapHeight(216), verticleFOV(60), horizontalFOV(120) {
  this->minimapTexture =
      SDL_CreateTexture(this->renderer->getSDLRenderer(),
                        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                        this->game->SCREEN_WIDTH, this->game->SCREEN_HEIGHT);
}

DEAD_Renderer3D::~DEAD_Renderer3D() {
  SDL_DestroyTexture(this->minimapTexture);
}

void DEAD_Renderer3D::render() {
  SDL_SetRenderTarget(this->renderer->getSDLRenderer(), this->renderer->getRenderTargetTexture());
  SDL_SetRenderDrawBlendMode(this->renderer->getSDLRenderer(),
                             SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), 10, 0, 10, 255);
  SDL_RenderClear(this->renderer->getSDLRenderer());

  double playerFacingDegree = this->game->getPlayer()->getRotation();
  double minPlayerFacingDegree = playerFacingDegree - this->horizontalFOV/2.0;
  double unitDegreePerX = this->horizontalFOV/(double)this->game->SCREEN_WIDTH;

  // render lines by x

  for (int x = 0; x < this->game->SCREEN_WIDTH; x++) {
    double tempDegree = DEAD_Functions::getDegreeFromZeroTo360(minPlayerFacingDegree + x*unitDegreePerX);
    
    SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), 255, 255, 255, 255);
    SDL_RenderDrawLine(this->renderer->getSDLRenderer(), x, 100, x, 200);
  }


  this->renderer->uiRenderer->render();
  this->renderer->playerInventoryRenderer->render();
  this->renderMinimap();
  this->renderer->renderYouDied();

  SDL_RenderPresent(this->renderer->getSDLRenderer());
}


void DEAD_Renderer3D::renderMinimap() {
  this->renderer->setRenderBlockSize(30);
  SDL_SetRenderTarget(this->renderer->getSDLRenderer(), this->minimapTexture);
  SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), 0, 0, 0, 0);
  SDL_RenderClear(this->renderer->getSDLRenderer());
  this->renderer->renderTargetTexture = this->minimapTexture;

  this->renderer->moveRenderAnchor(this->game->getPlayer()->getPos().x,
                                   this->game->getPlayer()->getPos().y,
                                   (int)(this->game->SCREEN_WIDTH / 2),
                                   (int)(this->game->SCREEN_HEIGHT / 2));

  this->renderer->renderMapObjects();
  this->renderer->decorationRenderer->render();
  this->renderer->renderItemDropLayer();
  this->renderer->renderBullets();
  this->renderer->renderPlayer(this->game->getPlayer());
  this->renderer->renderZombies(this->game->getZombieDirector());
  // this->drawZombieMovementMap();
  this->renderer->shadowCaster->render();
  this->renderer->renderPlayerMemoriable();
  this->renderer->particleRenderer->render();

  SDL_SetRenderTarget(this->renderer->getSDLRenderer(), NULL);
  SDL_Rect textureRect = {.x=(int)(this->game->SCREEN_WIDTH/2-this->minimapWidth/2),
                          .y=(int)(this->game->SCREEN_HEIGHT/2-this->minimapHeight/2),
                          .w=this->minimapWidth,
                          .h=this->minimapHeight};

  SDL_Rect screenRect = {.x = this->game->SCREEN_WIDTH - this->minimapWidth,
                         .y = 0,
                         .w = this->minimapWidth,
                         .h = this->minimapHeight};
  SDL_RenderCopy(this->renderer->getSDLRenderer(), this->minimapTexture, &textureRect,
                 &screenRect);

  this->renderer->renderTargetTexture = nullptr;
  SDL_SetRenderTarget(this->renderer->getSDLRenderer(), this->renderer->getRenderTargetTexture());

}
