#include "DEAD_weapon.h"
#include "DEAD_zombie_director.h"
#include "hitbox/DEAD_rect_hitbox.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <weapons/DEAD_bat.h>
#include <DEAD_player.h>
#include <DEAD_game.h>
#include <DEAD_particle_renderer.h>
#include <DEAD_zombie_director.h>
#include <DEAD_sound_director.h>
#include <DEAD_functions.h>

DEAD_Bat::DEAD_Bat(std::shared_ptr<DEAD_Player> owner) :
  DEAD_Weapon(owner, 500), angleEffectRange(100), effectDistance(2), damage(30) {

}

void DEAD_Bat::attack() {
  if (this->checkStillCooling() != 1.0) return;
  this->startCoolDown();

  DEAD_Map::MapLocation attackingLoc;
  DEAD_Vector attackingUnitVector = DEAD_Functions::calUnitVector(this->getPlayer()->getRotation());
  attackingLoc.x = this->getPlayer()->getPos().x + attackingUnitVector.x;
  attackingLoc.y = this->getPlayer()->getPos().y + attackingUnitVector.y;
  
  this->getPlayer()->getGame()->getRenderer()->getParticleRenderer()->playSwordAttackParticle(attackingLoc, this->getPlayer()->getRotation());
  this->getPlayer()->getGame()->getSoundDirector()->playBatSwingSound();

  std::shared_ptr<DEAD_ZombieDirector> zombieDirector;
  zombieDirector = this->getPlayer()->getGame()->getZombieDirector();
  std::set<std::shared_ptr<DEAD_Zombie>> zombies = zombieDirector->getZombies();

  DEAD_Map::MapLocation playerLoc = this->getPlayer()->getPos();

  for (std::shared_ptr<DEAD_Zombie> zombie : zombies) {
    double distance = DEAD_Functions::calDistance(playerLoc.x, playerLoc.y, zombie->getPos().x, zombie->getPos().y);
    double targetAngle = DEAD_Functions::calAngle(playerLoc.x, playerLoc.y, zombie->getPos().x, zombie->getPos().y);
    std::cout << "Target Angle: " << targetAngle << std::endl;
    double attackAngle = this->getPlayer()->getRotation();
    std::cout << "Attack Angle: " << attackAngle << std::endl;
    double deltaAngle = attackAngle - targetAngle;
    std::cout << "Delta Angle: " << deltaAngle << std::endl;
    
    while (int(deltaAngle/180) != 0) {
      if (deltaAngle > 0) deltaAngle -= 360;
      else if (deltaAngle < 0) deltaAngle += 360;
    }

    if (distance > effectDistance) continue;
    std::cout << "Distance Reached" << std::endl;
    if (!((deltaAngle >= 0 && deltaAngle <= this->angleEffectRange/2) || (deltaAngle < 0 && deltaAngle >= -this->angleEffectRange/2))) continue;
    std::cout << "Angle Correct" << std::endl;
    zombie->damage(this->damage);
  }
  // TODO: Implement Attack Range
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
