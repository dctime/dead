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
  DEAD_Weapon(owner), angleEffectRange(60), effectDistance(2) {

}

void DEAD_Bat::attack() {
  DEAD_Map::MapLocation attackingLoc;
  attackingLoc.x = this->getPlayer()->getPos().x + cos(this->getPlayer()->getRotation()/180*M_PI);
  attackingLoc.y = this->getPlayer()->getPos().y + sin(this->getPlayer()->getRotation()/180*M_PI);
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
    
    if (distance > effectDistance) continue;
    std::cout << "Distance Reached" << std::endl;
    if (!((deltaAngle >= 0 && deltaAngle <= this->angleEffectRange/2) || (deltaAngle < 0 && deltaAngle >= -this->angleEffectRange/2))) continue;
    std::cout << "Angle Correct" << std::endl;
    zombie->damage(100);
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
