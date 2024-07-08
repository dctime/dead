// https://web.archive.org/web/20210211164045/http://www.libsdl.org/

#include <DEAD_game.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_video.h>

int main() {
  DEAD_Game game = DEAD_Game();
  game.run();
  DEAD_Player::Position playerPos1 = {.x=1.5, .y=1.5};
  DEAD_Player player1 = DEAD_Player(&playerPos1);
  return 0;
}
