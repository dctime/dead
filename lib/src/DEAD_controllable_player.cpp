#include "DEAD_player.h"
#include <DEAD_controllable_player.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_scancode.h>
#include <iostream>

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
  if (state[SDL_SCANCODE_W] ) {
    std::cout << ("[ControllablePlayer] Move Up") << std::endl;
  } 

  if (state[SDL_SCANCODE_S]) {
    std::cout << ("[ControllablePlayer] Move Down") << std::endl;
  }

  if (state[SDL_SCANCODE_A]) {
    std::cout << ("[ControllablePlayer] Move Left") << std::endl;
  }

  if (state[SDL_SCANCODE_D]) {
    std::cout << ("[ControllablePlayer] Move Right") << std::endl;
  }
}
