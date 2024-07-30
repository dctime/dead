#include <memory>
#include <ui/DEAD_ui.h>
#include <DEAD_game.h>

DEAD_UI::DEAD_UI(DEAD_Renderer* renderer) 
  : game(renderer->getGame()), renderer(renderer) {
  
}

DEAD_UI::~DEAD_UI() {}
