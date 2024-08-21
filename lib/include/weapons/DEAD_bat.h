#include "../DEAD_weapon.h"
class DEAD_Bat : public DEAD_Weapon {
public:
  DEAD_Bat(DEAD_Player* owner);
  void attack() override;
  SDL_Rect getTextureRect() override;
  SDL_Rect getItemTextureRect() override;
  std::string getNote() override;
  std::string getName() override;
private:
  double angleEffectRange;
  double effectDistance;
  int damage;
};

