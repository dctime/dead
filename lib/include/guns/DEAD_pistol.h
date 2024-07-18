#include "DEAD_gun.h"
#include "../DEAD_player.h"
#include <memory>

class DEAD_Pistol : public DEAD_Gun, public std::enable_shared_from_this<DEAD_Pistol> {
public:
  DEAD_Pistol(DEAD_Player* player);
  ~DEAD_Pistol();
  SDL_Rect getTextureRect() override;
  void attack() override;
  double getBarrelLength() override;
  std::shared_ptr<DEAD_ItemDrop> getItemDrop() override;
};
