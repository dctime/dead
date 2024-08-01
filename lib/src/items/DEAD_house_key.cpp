#include "DEAD_player.h"
#include <items/DEAD_house_key.h>
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
}
