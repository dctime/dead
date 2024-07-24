#include "DEAD_ui.h"
#include <SDL2/SDL_rect.h>
#include "../DEAD_player.h"

class DEAD_PlayerHealthUI : public DEAD_UI {
public:
  DEAD_PlayerHealthUI(std::shared_ptr<DEAD_Renderer> renderer, std::shared_ptr<DEAD_Player> player);
  void render() override;
private:
  SDL_Rect healthBarRectBase;
  SDL_Rect healthBarRectJuice;
  int healthBarWidth;
  int healthBarHeight;
  int distanceBetweenScreenBoarder;
  int boarderWidth;
  std::shared_ptr<DEAD_Player> player;
};
