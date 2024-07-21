#include <SDL2/SDL_rect.h>
#include <iostream>
#include <memory>
#include <zombies/DEAD_zombie.h>

DEAD_Zombie::DEAD_Zombie(std::shared_ptr<DEAD_Game> game) : DEAD_Entity::DEAD_Entity(game) {
  std::cout << "Zombie Built" << std::endl;
}

SDL_Rect DEAD_Zombie::getTextureRect() {
  SDL_Rect rect = {.x=0, .y=0, .w=100, .h=100};
  return rect; 
};


  
