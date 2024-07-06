#include <DEAD_game.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL.h>

DEAD_Game::DEAD_Game(const char* mapFilePath) {

  SDL_Log("Game Init");
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
      SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
  }

  this->window = SDL_CreateWindow("DEAD", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                            this->SCREEN_WIDTH, this->SCREEN_HEIGHT, SDL_WINDOW_SHOWN); 
  if (window == NULL) {
    SDL_Log("Unable to init window: %s", SDL_GetError());
  }
  
  DEAD_Map map = DEAD_Map(mapFilePath);
  this->map = &map;

}

DEAD_Game::~DEAD_Game() {
  SDL_DestroyWindow(this->window);
  SDL_Quit();
  SDL_Log("Game Destroyed");
}

void DEAD_Game::tick() {
  this->eventHandle();
}

void DEAD_Game::eventHandle() {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
    case SDL_QUIT:
      this->running = false;      
  }
}

void DEAD_Game::run() {
  while (this->running) {
    this->tick();
  }
}


