#include <DEAD_ui_renderer.h>
#include <ui/DEAD_player_health_ui.h>
#include <DEAD_renderer.h>
#include <DEAD_game.h>
#include <memory>

DEAD_UIRenderer::DEAD_UIRenderer(std::shared_ptr<DEAD_Renderer> renderer) {
  this->uis.push_back(std::make_shared<DEAD_PlayerHealthUI>(renderer, renderer->getGame()->getPlayer()));
}

void DEAD_UIRenderer::render() {
  for (std::shared_ptr<DEAD_UI> ui : this->uis) {
    ui->render();
  }
}
