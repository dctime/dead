#include "DEAD_player.h"
#include <DEAD_weapon.h>
#include <memory>

DEAD_Weapon::~DEAD_Weapon() {}

DEAD_Weapon::DEAD_Weapon(std::shared_ptr<DEAD_Player> player)
  : DEAD_Item() {
  this->owner = player;
}

std::shared_ptr<DEAD_Player> DEAD_Weapon::getPlayer() {
  return this->owner;
}

