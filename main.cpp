// https://web.archive.org/web/20210211164045/http://www.libsdl.org/

#include <DEAD_game.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_video.h>

int main() {
  DEAD_Map::MapLocation playerPos = {.x=-2, .y=-2};
  DEAD_ControllablePlayer player = DEAD_ControllablePlayer(&playerPos);
  DEAD_Game game = DEAD_Game(&player);
  game.run();
  return 0;
}
