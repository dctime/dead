// https://web.archive.org/web/20210211164045/http://www.libsdl.org/

#include <DEAD_game.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_video.h>

int main() {
  DEAD_ControllablePlayer player = DEAD_ControllablePlayer();
  DEAD_Game game = DEAD_Game(&player);
  game.run();
  


}
