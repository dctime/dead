#include "DEAD_ui.h"
#include "../DEAD_renderer.h"
#include <SDL2/SDL_ttf.h>

class DEAD_ZombieIndicatorUI : public DEAD_UI {
public:
  DEAD_ZombieIndicatorUI(DEAD_Renderer* renderer);
  ~DEAD_ZombieIndicatorUI();
  void render() override;
  void updateFontTexture();
private:
  TTF_Font* font;
  ScreenLocation loc;
  SDL_Texture* zombiesLeftFontTexture;
  SDL_Texture* zombieKillcountFontTexture;
};
