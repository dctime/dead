#include <map_objects/DEAD_player_memoriable_object.h>

DEAD_PlayerMemoriableManager::DEAD_PlayerMemoriableManager()
  : visible(false), alpha(0) {
  
}

bool DEAD_PlayerMemoriableManager::isVisible() {
  return this->visible;
}

void DEAD_PlayerMemoriableManager::setToVisible() {
  this->visible = true;
}

int DEAD_PlayerMemoriableManager::getAlpha() {
  return this->alpha;
}

void DEAD_PlayerMemoriableManager::gainAlpha(int value) {
  this->alpha += value;
  if (this->alpha > 255) {
    this->alpha = 255;
  }
}
