// https://web.archive.org/web/20210211164045/http://www.libsdl.org/

#include <DEAD_game.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_video.h>
#include <memory>

int main() {


  std::shared_ptr<DEAD_ControllablePlayer> player = std::make_shared<DEAD_ControllablePlayer>();
  std::shared_ptr<DEAD_Game> game = std::make_shared<DEAD_Game>(player);
  game->run();
  


}
