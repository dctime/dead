#include "DEAD_gun.h"
#include <memory>

class DEAD_Shotgun : public DEAD_Gun, public std::enable_shared_from_this<DEAD_Shotgun> {
public:
  DEAD_Shotgun(DEAD_Player* player);
  ~DEAD_Shotgun();
  SDL_Rect getTextureRect() override;
  std::shared_ptr<DEAD_ItemDrop> getItemDrop() override;
};
