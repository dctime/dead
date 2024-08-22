#include <DEAD_player.h>
#include <items/weapons/DEAD_weapon.h>

DEAD_Weapon::~DEAD_Weapon() {}

DEAD_Weapon::DEAD_Weapon(DEAD_Player* player, const int COOLDOWN_TIME)
  : DEAD_Item(player), COOLDOWN_TIME(COOLDOWN_TIME), 
    startCoolingTicks(0) {
}

void DEAD_Weapon::startCoolDown() {
  this->startCoolingTicks = SDL_GetTicks64();
}

// 0.0 - 1.0, means not cooling;
double DEAD_Weapon::checkStillCooling() {
  int nowTicks = SDL_GetTicks64();
  int coolingTicks = nowTicks - this->startCoolingTicks;
  if (coolingTicks >= this->COOLDOWN_TIME) return 1.0;
  else return static_cast<double>(coolingTicks) / this->COOLDOWN_TIME;
}

