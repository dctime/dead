#include <SDL2/SDL_rect.h>
#include <iostream>
#include <zombies/DEAD_zombie.h>

DEAD_Zombie::DEAD_Zombie() {
  std::cout << "Zombie Built" << std::endl;
}

SDL_Rect DEAD_Zombie::getTextureRect() {
  SDL_Rect rect = {.x=0, .y=0, .w=100, .h=100};
  return rect; 
};
  
