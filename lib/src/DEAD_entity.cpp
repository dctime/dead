#include "DEAD_entity.h"
#include <DEAD_game.h>
#include <guns/DEAD_pistol.h>
#include <memory>

DEAD_Entity::DEAD_Entity()
: speed(3), position({.x=0, .y=0}), rotation(0), size(0.8) {
  this->hitbox = std::make_shared<DEAD_CircleHitbox>(this->getSize() / 2 * 0.8, this->position);
}

DEAD_Entity::~DEAD_Entity() {
  SDL_Log("Entity Destoryed");
}

DEAD_Map::MapLocation DEAD_Entity::getPos() {
  return this->position;
}

void DEAD_Entity::setPos(double x, double y) {
  this->position.x = x;
  this->position.y = y;
  this->hitbox->setLoc(this->position);
}

void DEAD_Entity::setSpeed(int speed) {
  this->speed = speed;
}

void DEAD_Entity::setRotation(double rotation) {
  this->rotation = rotation;
}


int DEAD_Entity::getSpeed() {
  return this->speed;
}

double DEAD_Entity::getRotation() {
  return this->rotation; 
}

void DEAD_Entity::setGame(std::shared_ptr<DEAD_Game> game) {
  this->game = game;
}

std::shared_ptr<DEAD_Game> DEAD_Entity::getGame() {
  return this->game;
}

void DEAD_Entity::move(double x, double y) {
  if (this->getGame()->getCollisionDirector()->entityCheckCollision(shared_from_this(), x*100, y*100).size() != 0) {
    return;
  } else {
    this->setPos(this->getPos().x+x, this->getPos().y+y);
  }
}

double DEAD_Entity::getSize() { return this->size; }
std::shared_ptr<DEAD_CircleHitbox> DEAD_Entity::getHitbox() { return this->hitbox; }

double DEAD_Entity::getPickItemRadius() {
  return 1;
}
