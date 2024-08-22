#include "DEAD_entity.h"
#include <DEAD_game.h>
#include <SDL2/SDL_timer.h>
#include <cstdlib>
#include <items/weapons/guns/DEAD_pistol.h>
#include <iostream>
#include <memory>

DEAD_Entity::DEAD_Entity(DEAD_Game* game, int maxHealth, double size)
    : speed(3), position({.x = 0, .y = 0}), rotation(0), size(size), maxHealth(maxHealth), health(maxHealth),
      lastTimeBeenHitTicks(0), knockBackCooldown(300), holdItem(nullptr), entityName("") {
  this->hitbox = std::make_unique<DEAD_CircleHitbox>(size / 2.5,
                                                     this->position);
  this->setGame(game);
}

void DEAD_Entity::damage(int damage) {
  this->lastTimeBeenHitTicks = SDL_GetTicks64();
  int newHealth = this->health - damage;
  if(newHealth < 0) {
    this->health = 0;
  } else {
    this->health = newHealth;
  }
  std::cout << "New health: " << this->health << std::endl;
}

DEAD_Entity::~DEAD_Entity() { SDL_Log("Entity Destoryed"); }

bool DEAD_Entity::checkIfInKnockback() {
  if (SDL_GetTicks64() - this->lastTimeBeenHitTicks < this->knockBackCooldown) return true; 
  else return false;
}

int DEAD_Entity::getMaxhealth() {
  return this->maxHealth;
}

int DEAD_Entity::getHealth() {
  return this->health;
}

bool DEAD_Entity::checkhealthIsDead() {
  if (this->health <= 0) {
    return true;
  }
  return false;
}

void DEAD_Entity::setEntityName(std::string name) {
  this->entityName = name;
}

std::string DEAD_Entity::getEntityName() {
  return this->entityName;
}

std::shared_ptr<DEAD_Item> DEAD_Entity::getHoldItem() {
  return this->holdItem;
}

void DEAD_Entity::setMaxHealth(int maxHealth) {
  this->maxHealth = maxHealth;
}

void DEAD_Entity::setHealth(int health) {
  this->health = health;
} 

DEAD_Map::MapLocation DEAD_Entity::getPos() { return this->position; }

void DEAD_Entity::setPos(double x, double y) {
  this->position.x = x;
  this->position.y = y;
  this->hitbox->setLoc(this->position);
}

void DEAD_Entity::setSpeed(int speed) { this->speed = speed; }

void DEAD_Entity::setRotation(double rotation) { this->rotation = rotation; }

int DEAD_Entity::getSpeed() { return this->speed; }

DEAD_Game* DEAD_Entity::getGame() {
  return this->game;
}

double DEAD_Entity::getSize() {
  return this->size;
}

DEAD_CircleHitbox* DEAD_Entity::getHitbox() {
  this->hitbox->setLoc(this->getPos());
  return this->hitbox.get(); 
}

void DEAD_Entity::move(double x, double y) {
  if (this->getGame()->getCollisionDirector()->entityCheckCollision(this, x, y).size() != 0) {
    return;
  } else {
    // FIXME: Integrate speed and collision in move not objects that calls move function
    this->setPos(this->getPos().x+x, this->getPos().y+y);
  }
}

void DEAD_Entity::setGame(DEAD_Game* game) {
  this->game = game;
}

double DEAD_Entity::getRotation() { return this->rotation; }

double DEAD_Entity::getPickItemRadius() { return 1; }
