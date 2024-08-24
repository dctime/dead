#include "subrenderers/DEAD_decoration_renderer.h"
#include <DEAD_controllable_player.h>
#include <DEAD_game.h>
#include <DEAD_renderer.h>
#include <DEAD_renderer3d.h>
#include <subrenderers/DEAD_shadow_caster.h>
#include <subrenderers/DEAD_explainer.h>
#include <subrenderers/DEAD_ui_renderer.h>
#include <subrenderers/DEAD_player_inventory_renderer.h>

DEAD_Renderer3D::DEAD_Renderer3D(SDL_Window *window, DEAD_Renderer *renderer,
                                 DEAD_Game *game)
    : window(window), renderer(renderer), game(game) {}

void DEAD_Renderer3D::render() {
  this->renderer->uiRenderer->render();
  this->renderer->playerInventoryRenderer->render();
  this->renderer->explainer->render();
  this->renderMinimap();
  this->renderer->renderYouDied();

  SDL_RenderPresent(this->renderer->getSDLRenderer());
}

void DEAD_Renderer3D::renderMinimap() {
  this->renderer->moveRenderAnchor(this->game->getPlayer()->getPos().x,
                                   this->game->getPlayer()->getPos().y,
                                   this->game->SCREEN_WIDTH - 100, 100);
  SDL_SetRenderDrawBlendMode(this->renderer->getSDLRenderer(),
                             SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), 10, 0, 10, 255);
  SDL_RenderClear(this->renderer->getSDLRenderer());

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


}
