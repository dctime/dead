// https://web.archive.org/web/20210211164045/http://www.libsdl.org/

#include <DEAD_game.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_video.h>
#include <memory>
#include <DEAD_game_builder.h>
int main() {


  std::shared_ptr<DEAD_ControllablePlayer> player = std::make_shared<DEAD_ControllablePlayer>();
  std::shared_ptr<DEAD_GameBuilder> gameBuilder = std::make_shared<DEAD_GameBuilder>(player);
  std::shared_ptr<DEAD_Game> game = gameBuilder->build();
  game->run();
  


}
