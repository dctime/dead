#include <SDL2/SDL_log.h>
#include <map_objects/DEAD_wood.h>
#include <SDL2/SDL.h>
DEAD_Wood::DEAD_Wood() {
  SDL_Log("init wood");
}

char DEAD_Wood::getChar() { return 'w'; }
