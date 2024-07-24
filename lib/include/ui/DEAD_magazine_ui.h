#include "../ui/DEAD_ui.h"
#include <memory>
#include "DEAD_value_bar_ui_element.h"

class DEAD_MagazineUI : public DEAD_UI {
public:
  DEAD_MagazineUI(std::shared_ptr<DEAD_Renderer> renderer, std::shared_ptr<DEAD_Player> player);
  void render() override;
private:
  

  int magazineUIWidth;
  int magazineUIHeight;
  int distanceBetweenScreenBoarder;
  int boarderWidth;
  std::shared_ptr<DEAD_ValueBarUIElement> barElement;
  std::shared_ptr<DEAD_Renderer> renderer;
  std::shared_ptr<DEAD_Player> player;
};
