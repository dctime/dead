#include "DEAD_weapon.h"
#include <cmath>
#include <memory>
#include <weapons/DEAD_bat.h>
#include <DEAD_player.h>
#include <DEAD_game.h>
#include <DEAD_particle_renderer.h>

DEAD_Bat::DEAD_Bat(std::shared_ptr<DEAD_Player> owner) :
  DEAD_Weapon(owner) {

}

void DEAD_Bat::attack() {
  DEAD_Map::MapLocation attackingLoc;
  attackingLoc.x = this->getPlayer()->getPos().x + cos(this->getPlayer()->getRotation()/180*M_PI);
  attackingLoc.y = this->getPlayer()->getPos().y + sin(this->getPlayer()->getRotation()/180*M_PI);
  this->getPlayer()->getGame()->getRenderer()->getParticleRenderer()->playSwordAttackParticle(attackingLoc, this->getPlayer()->getRotation());
}

SDL_Rect DEAD_Bat::getTextureRect() {
  SDL_Rect rect = {.x=200, .y=0, .w=100, .h=100};
  return rect;
}

SDL_Rect DEAD_Bat::getItemTextureRect() {
  SDL_Rect rect = {.x=100, .y=0, .w=100, .h=100};
  return rect;
}

std::shared_ptr<DEAD_ItemDrop> DEAD_Bat::getItemDrop() {
  if (this->itemDrop == nullptr) {
    this->itemDrop = std::make_shared<DEAD_ItemDrop>(shared_from_this(), this->getPlayer()->getPos());
  }

  return this->itemDrop;
}
