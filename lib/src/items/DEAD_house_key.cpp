#include "DEAD_functions.h"
#include "DEAD_player.h"
#include <items/DEAD_house_key.h>
#include <map_objects/DEAD_door.h>
#include <DEAD_game.h>
#include <iostream>

DEAD_HouseKey::DEAD_HouseKey(DEAD_Player* owner)
  : DEAD_Item(owner) {
  
}

SDL_Rect DEAD_HouseKey::getTextureRect() {
  return {.x=300, .y=0, .w=100, .h=100};  
}

SDL_Rect DEAD_HouseKey::getItemTextureRect() {
  return {.x=200, .y=0, .w=100, .h=100}; 
}

void DEAD_HouseKey::use() {
  std::cout << "using the key" << std::endl;
  double angle = this->getPlayer()->getRotation();
  DEAD_Vector targetVector = DEAD_Functions::calUnitVector(angle);
  DEAD_Map::MapLocation targetLoc = {.x=targetVector.x + this->getPlayer()->getPos().x, .y=targetVector.y + this->getPlayer()->getPos().y};
  DEAD_MapObjectBase* targetObject = this->getPlayer()->getGame()->getMap()->getMapObject((int)targetLoc.x, (int)targetLoc.y);
  DEAD_Door* door = dynamic_cast<DEAD_Door*>(targetObject);
  if (door == nullptr) return;
  door->openDoor();
}
