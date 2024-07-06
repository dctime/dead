#include <SDL2/SDL_video.h>
#include "DEAD_map.h"

class DEAD_Game {
public:
  DEAD_Game(const char* mapFilePath);
  ~DEAD_Game();
  void tick();
  void run();
  const int SCREEN_WIDTH = 720;
  const int SCREEN_HEIGHT = 480;
private:
  SDL_Window* window;
  DEAD_Map* map;
  void eventHandle();
  bool running = true;
};
