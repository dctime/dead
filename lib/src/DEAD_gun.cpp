#include "DEAD_weapon.h"
#include <DEAD_gun.h>
#include <DEAD_normal_bullet.h>

DEAD_Gun::DEAD_Gun()
: DEAD_Weapon(nullptr) {}

DEAD_Gun::DEAD_Gun(DEAD_Player* player)
  : DEAD_Weapon(player) {}

