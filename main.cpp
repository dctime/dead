// https://web.archive.org/web/20210211164045/http://www.libsdl.org/

#include <DEAD_game.h>
#include <DEAD_game_builder.h>

int main(int argc, char **argv) {
  std::string playerName;
  if (argc != 2) {
    std::cout << "Must Pass In One Argument as the player name" << std::endl;
    playerName = "Player";
  } else {
    playerName = argv[0];
  }
    
  std::shared_ptr<DEAD_Game> game;
  // if (dead::pressedPlay == true) {
  std::shared_ptr<DEAD_GameBuilder> gameBuilder =
      std::make_shared<DEAD_GameBuilder>(playerName);
  game = gameBuilder->build();
  // }

  game->run();
}

