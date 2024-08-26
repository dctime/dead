#include "player_input_method/DEAD_player_input_method.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <player_input_method/DEAD_player_input_method_3d.h>
#include <DEAD_controllable_player.h>
#include <DEAD_functions.h>
#include <iostream>

DEAD_PlayerInputMethod3D::DEAD_PlayerInputMethod3D(DEAD_ControllablePlayer* player, double baseSpeed) 
  : DEAD_PlayerInputMethod(player), baseSpeed(baseSpeed) {
}

void DEAD_PlayerInputMethod3D::handleKeyState() {
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  double moveTickDistance = this->baseSpeed * player->getSpeed();
  DEAD_Vector moveUnitVector = {.x=0, .y=0};

  
  if (state[SDL_SCANCODE_W]) {
    double rotation = this->player->getRotation();
    moveUnitVector = DEAD_Functions::calUnitVector(rotation);
    player->move(moveUnitVector.x * moveTickDistance, 0);
    player->move(0, moveUnitVector.y * moveTickDistance);
  }

  if (state[SDL_SCANCODE_S]) {
    double rotation = this->player->getRotation();
    rotation = DEAD_Functions::getDegreeFromZeroTo360(rotation + 180);
    moveUnitVector = DEAD_Functions::calUnitVector(rotation);
    player->move(moveUnitVector.x * moveTickDistance, 0);
    player->move(0, moveUnitVector.y * moveTickDistance);
  }

  if (state[SDL_SCANCODE_A]) {
    double rotation = this->player->getRotation();
    rotation = DEAD_Functions::getDegreeFromZeroTo360(rotation - 90);
    moveUnitVector = DEAD_Functions::calUnitVector(rotation);
    player->move(moveUnitVector.x * moveTickDistance, 0);
    player->move(0, moveUnitVector.y * moveTickDistance);
  }

  if (state[SDL_SCANCODE_D]) {
    double rotation = this->player->getRotation();
    rotation = DEAD_Functions::getDegreeFromZeroTo360(rotation + 90);
    moveUnitVector = DEAD_Functions::calUnitVector(rotation);
    player->move(moveUnitVector.x * moveTickDistance, 0);
    player->move(0, moveUnitVector.y * moveTickDistance);
  }

  if (state[SDL_SCANCODE_LCTRL]) {
    SDL_SetRelativeMouseMode(SDL_FALSE);
    this->mouseRelative = false;
  } else {
    SDL_SetRelativeMouseMode(SDL_TRUE);
    this->mouseRelative = true;
  }

  
}

void DEAD_PlayerInputMethod3D::handlePlayerRotation() {
  if (!this->mouseRelative) { return; }
  int x, y;
  SDL_GetRelativeMouseState(&x, &y);
  double sensitivity = 0.05;
  player->setRotation(player->getRotation()+x*sensitivity);
}
