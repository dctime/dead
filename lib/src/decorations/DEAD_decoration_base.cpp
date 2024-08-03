#include <decorations/DEAD_decoration_base.h>
#include <iostream>
#include <DEAD_controllable_player.h>


DEAD_DecorationBase::DEAD_DecorationBase(DEAD_Map::MapLocation loc,
                                         double width, double height,
                                         double rotationAngle,
                                         double interactRadius)
    : loc(loc), width(width), height(height), rotationAngle(rotationAngle),
      interactHitbox(std::make_unique<DEAD_CircleHitbox>(interactRadius, loc)) {
}

DEAD_Map::MapLocation DEAD_DecorationBase::getLoc() { return this->loc; }

double DEAD_DecorationBase::getWidth() { return this->width; }

double DEAD_DecorationBase::getHeight() { return this->height; }

double DEAD_DecorationBase::getRotationAngle() { return this->rotationAngle; }

DEAD_CircleHitbox* DEAD_DecorationBase::getInteractHitbox() {
  return this->interactHitbox.get();
}

bool DEAD_DecorationBase::destroying(int ticksInterval, DEAD_ControllablePlayer* player) {
  if (ticksInterval >= this->destroyRequireTicks()) { 
    this->destroyPercentage = 1.0;
    return true;
  } else {
    this->destroyPercentage = (double)ticksInterval / this->destroyRequireTicks(); 
    std::cout << "Destory Percentage: " << this->destroyPercentage << std::endl;
  }
  return false;
}

void DEAD_DecorationBase::destroy() {
  std::cout << "Destroyed" << std::endl;
}

double DEAD_DecorationBase::getDestroyPercentage() {
  return this->destroyPercentage;
}
