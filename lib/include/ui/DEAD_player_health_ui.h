#include "DEAD_ui.h"
#include <SDL2/SDL_rect.h>
#include <memory>
#include "../DEAD_player.h"
#include "DEAD_value_bar_ui_element.h"

class DEAD_PlayerHealthUI : public DEAD_UI {
public:
  DEAD_PlayerHealthUI(DEAD_Renderer* renderer, DEAD_Player* player);
  void render() override;
private:
  SDL_Rect healthBarRectBase;
  SDL_Rect healthBarRectJuice;
  int healthBarWidth;
  int healthBarHeight;
  int distanceBetweenScreenBoarder;
  int boarderWidth;
  DEAD_Player* player;
  std::unique_ptr<DEAD_ValueBarUIElement> barElement;
};
