#include <DEAD_game.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
DEAD_Game::DEAD_Game(const char *mapFilePath) {

  SDL_Log("Game Init");
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
  }

  // load support for the JPG and PNG image formats
  int flags = IMG_INIT_PNG;
  int initted = IMG_Init(flags);
  if ((initted & flags) != flags) {
    printf("IMG_Init: Failed to init required png support!\n");
    printf("IMG_Init: %s\n", IMG_GetError());
    // handle error
  }

  this->window = SDL_CreateWindow("DEAD", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, this->SCREEN_WIDTH,
                                  this->SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    SDL_Log("Unable to init window: %s", SDL_GetError());
  }

  DEAD_Map map = DEAD_Map(mapFilePath);
  this->map = &map;

  this->renderer =
      SDL_CreateRenderer(this->window, 0, SDL_RENDERER_ACCELERATED);
}

DEAD_Game::~DEAD_Game() {
  SDL_DestroyWindow(this->window);
  SDL_DestroyRenderer(this->renderer);
  IMG_Quit();
  SDL_Quit();
  SDL_Log("Game Destroyed");
}

void DEAD_Game::tick() {
  this->eventHandle();
  this->render();
}

void DEAD_Game::eventHandle() {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    this->running = false;
  }
}

void DEAD_Game::render() {
  SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
  SDL_RenderClear(this->renderer);

  SDL_Surface *mapObjectSurface = IMG_Load("assets/imgs/map_objects.png");
  SDL_Texture *mapObjectTexture = SDL_CreateTextureFromSurface(this->renderer, mapObjectSurface);
  SDL_FreeSurface(mapObjectSurface);
  
  SDL_Rect stoneLocationRect = {.x=0, .y=0, .w=100, .h=100 };
  SDL_Rect renderRect = {.x=10, .y=10, .w=30, .h=30};
  
  SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 0);
  SDL_RenderCopy(this->renderer, mapObjectTexture, &stoneLocationRect, &renderRect);
  SDL_GetError();
  
  SDL_RenderPresent(this->renderer);
}

void DEAD_Game::run() {
  while (this->running) {
    this->tick();
  }
}
