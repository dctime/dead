#include "subrenderers/DEAD_subrenderer_base.h"
#include <subrenderers/DEAD_ui_renderer.h>
#include <ui/DEAD_player_health_ui.h>
#include <ui/DEAD_zombie_indicator_ui.h>
#include <ui/DEAD_magazine_ui.h>
#include <DEAD_renderer.h>
#include <DEAD_game.h>
#include <memory>

DEAD_UIRenderer::DEAD_UIRenderer(DEAD_Renderer* renderer) 
  : DEAD_SubRendererBase(renderer) {
  this->uis.push_back(std::make_unique<DEAD_PlayerHealthUI>(renderer, renderer->getGame()->getPlayer()));
  this->uis.push_back(std::make_unique<DEAD_MagazineUI>(renderer, renderer->getGame()->getPlayer()));
  this->uis.push_back(std::make_unique<DEAD_ZombieIndicatorUI>(renderer));
}

void DEAD_UIRenderer::render() {
  SDL_SetRenderTarget(this->renderer->getSDLRenderer(), this->renderer->getRenderTargetTexture());

  for (std::unique_ptr<DEAD_UI>& ui : this->uis) {
    ui->render();
  }
}
