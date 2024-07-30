#include "../DEAD_weapon.h"
class DEAD_Bat : public DEAD_Weapon {
public:
  DEAD_Bat(DEAD_Player* owner);
  void attack() override;
  SDL_Rect getTextureRect() override;
  SDL_Rect getItemTextureRect() override;
  std::shared_ptr<DEAD_ItemDrop> getItemDrop() override;
private:
  double angleEffectRange;
  double effectDistance;
  int damage;
};

