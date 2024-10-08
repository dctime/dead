#include "DEAD_gun.h"
#include <memory>

class DEAD_Shotgun : public DEAD_Gun {
public:
  DEAD_Shotgun(DEAD_Player* player);
  ~DEAD_Shotgun();
  SDL_Rect getTextureRect() override;
  SDL_Rect getItemTextureRect() override;
  std::string getName() override;
  std::string getNote() override;
};
