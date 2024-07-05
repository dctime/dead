// https://web.archive.org/web/20210211164045/http://www.libsdl.org/

#include <DEAD_map.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_video.h>

int main() {

  Map map;

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return 1;
  }

  SDL_Window *window =
      SDL_CreateWindow("dead", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       720, 480, SDL_WINDOW_SHOWN);

  if (window == NULL) {
    SDL_Log("Unable to init window: %s", SDL_GetError());
  }

  bool running = true;
  while (running) {
    // Event handling
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
    case (SDL_QUIT):
      SDL_Log("Quit SDL2");
      running = false;
    }
  }
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
