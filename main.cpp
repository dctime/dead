// https://web.archive.org/web/20210211164045/http://www.libsdl.org/

#include <DEAD_controllable_player.h>
#include <DEAD_game.h>
#include <DEAD_game_builder.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_video.h>
#include <memory>

int main() {
  std::shared_ptr<DEAD_GameBuilder> gameBuilder =
      std::make_shared<DEAD_GameBuilder>();
  std::shared_ptr<DEAD_Game> game = gameBuilder->build();

  game->run();
}
