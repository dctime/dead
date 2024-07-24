#include "DEAD_gun.h"
#include "../DEAD_player.h"
#include <memory>

class DEAD_Pistol : public DEAD_Gun {
public:
  DEAD_Pistol(std::shared_ptr<DEAD_Player> player);
  ~DEAD_Pistol();
  SDL_Rect getTextureRect() override;
  void attack() override;
  double getBarrelLength() override;
  std::shared_ptr<DEAD_ItemDrop> getItemDrop() override;
  virtual SDL_Rect getItemTextureRect() override;
  int getMagazineSize();
  void reload() override; 
  
};
