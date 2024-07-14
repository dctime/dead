#include "DEAD_player.h"
#include <DEAD_weapon.h>
#include <iostream>

DEAD_Weapon::DEAD_Weapon(DEAD_Player* player) {
  this->owner = player;
}

DEAD_Player* DEAD_Weapon::getPlayer() {
  return this->owner;
}

