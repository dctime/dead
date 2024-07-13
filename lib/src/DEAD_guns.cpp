#include "DEAD_weapon.h"
#include <DEAD_guns.h>

DEAD_Guns::DEAD_Guns()
: DEAD_Weapon(nullptr) {}

DEAD_Guns::DEAD_Guns(DEAD_Player* player)
  : DEAD_Weapon(player) {}

void DEAD_Guns::shoot() {
  
}
