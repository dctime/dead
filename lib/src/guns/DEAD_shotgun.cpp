#include "DEAD_player.h"
#include "guns/DEAD_gun.h"
#include <SDL2/SDL_rect.h>
#include <guns/DEAD_shotgun.h>

DEAD_Shotgun::DEAD_Shotgun(DEAD_Player* player)
  : DEAD_Gun(player) {

}
DEAD_Shotgun::~DEAD_Shotgun() {}
SDL_Rect DEAD_Shotgun::getTextureRect() {
  SDL_Rect rect = {.x=200, .y=0, .w=100, .h=100};
  return rect;
}

std::shared_ptr<DEAD_ItemDrop> DEAD_Shotgun::getItemDrop() {
  if (this->itemDrop == nullptr) {
    this->itemDrop = std::make_shared<DEAD_ItemDrop>(shared_from_this(), this->getPlayer()->getPos());
  }

  return this->itemDrop;
}

SDL_Rect DEAD_Shotgun::getItemTextureRect() {
  SDL_Rect rect = {.x=100, .y=0, .w=100, .h=100};
  return rect;
}
