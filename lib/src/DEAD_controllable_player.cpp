#include "DEAD_player.h"
#include <DEAD_controllable_player.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_scancode.h>

DEAD_ControllablePlayer::DEAD_ControllablePlayer(DEAD_Player::Position *pos)
    : DEAD_Player::DEAD_Player(pos) {}

DEAD_ControllablePlayer::~DEAD_ControllablePlayer() {}

void DEAD_ControllablePlayer::playerEvents(SDL_Event event) {
  switch (event.type) {
  default:
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    handleKeyState(state);
  }
}

void DEAD_ControllablePlayer::handleKeyState(const Uint8* state) {
  double moveTickDistance = this->baseSpeed * this->getSpeed();
  if (state[SDL_SCANCODE_W] ) {
    this->setPos(this->getPos()->x, this->getPos()->y - moveTickDistance);
  } 

  if (state[SDL_SCANCODE_S]) {
    this->setPos(this->getPos()->x, this->getPos()->y + moveTickDistance); 
  }

  if (state[SDL_SCANCODE_A]) {
    this->setPos(this->getPos()->x - moveTickDistance, this->getPos()->y); 
  }

  if (state[SDL_SCANCODE_D]) {
    this->setPos(this->getPos()->x + moveTickDistance, this->getPos()->y); 
  }
}
