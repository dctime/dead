#include <DEAD_weapon.h>
#include <guns/DEAD_gun.h>
#include <bullets/DEAD_normal_bullet.h>
#include <memory>

DEAD_Gun::DEAD_Gun(std::shared_ptr<DEAD_Player> player)
  : DEAD_Weapon(player) {}


DEAD_Gun::~DEAD_Gun() {}

