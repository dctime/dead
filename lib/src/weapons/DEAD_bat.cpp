#include "DEAD_weapon.h"
#include "DEAD_zombie_director.h"
#include "hitbox/DEAD_rect_hitbox.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <weapons/DEAD_bat.h>
#include <DEAD_player.h>
#include <DEAD_game.h>
#include <subrenderers/DEAD_particle_renderer.h>
#include <DEAD_zombie_director.h>
#include <DEAD_sound_director.h>
#include <DEAD_functions.h>

DEAD_Bat::DEAD_Bat(DEAD_Player* owner) :
  DEAD_Weapon(owner, 500), angleEffectRange(100), effectDistance(2), damage(10) {

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

  DEAD_ZombieDirector* zombieDirector;
  zombieDirector = this->getPlayer()->getGame()->getZombieDirector();
  std::set<std::unique_ptr<DEAD_Zombie>>& zombies = zombieDirector->getZombies();

  DEAD_Map::MapLocation playerLoc = this->getPlayer()->getPos();

  for (const std::unique_ptr<DEAD_Zombie>& zombie : zombies) {
    double distance = DEAD_Functions::calDistance(playerLoc.x, playerLoc.y, zombie->getPos().x, zombie->getPos().y);
    double targetAngle = DEAD_Functions::calAngle(playerLoc.x, playerLoc.y, zombie->getPos().x, zombie->getPos().y);
    double attackAngle = this->getPlayer()->getRotation();
    double deltaAngle = attackAngle - targetAngle;
    
    while (int(deltaAngle/180) != 0) {
      if (deltaAngle > 0) deltaAngle -= 360;
      else if (deltaAngle < 0) deltaAngle += 360;
    }

    if (distance > effectDistance) continue;
    if (!((deltaAngle >= 0 && deltaAngle <= this->angleEffectRange/2) || (deltaAngle < 0 && deltaAngle >= -this->angleEffectRange/2))) continue;
    this->getPlayer()->getGame()->getSoundDirector()->playHitWithBat();
    zombie->damage(this->damage, this->getPlayer());
  }
}

SDL_Rect DEAD_Bat::getTextureRect() {
  SDL_Rect rect = {.x=200, .y=0, .w=100, .h=100};
  return rect;
}

SDL_Rect DEAD_Bat::getItemTextureRect() {
  SDL_Rect rect = {.x=100, .y=0, .w=100, .h=100};
  return rect;
}

std::string DEAD_Bat::getNote() {
  return "Short range AOE melee weapon";
}

std::string DEAD_Bat::getName() {
  return "Bat";
}

