#include "DEAD_controllable_player.h"
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>
#include <player_input_method/DEAD_player_input_method_2d.h>
#include <DEAD_game.h>

DEAD_PlayerInputMethod2D::DEAD_PlayerInputMethod2D(DEAD_ControllablePlayer* player, double baseSpeed) 
  : DEAD_PlayerInputMethod(player), baseSpeed(baseSpeed) {
  
}

void DEAD_PlayerInputMethod2D::handleKeyState() {
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  double moveTickDistance = this->baseSpeed * player->getSpeed();
  bool moved = false;
  

  if (state[SDL_SCANCODE_W]) {
    player->move(0, -moveTickDistance);
  }

  if (state[SDL_SCANCODE_S]) {

    player->move(0, moveTickDistance);
  }

  if (state[SDL_SCANCODE_A]) {
    player->move(-moveTickDistance, 0);
  }

  if (state[SDL_SCANCODE_D]) {
    player->move(moveTickDistance, 0);
  }
}

void DEAD_PlayerInputMethod2D::handlePlayerRotation() {
  SDL_SetRelativeMouseMode(SDL_FALSE);
  int mouseX;
  int mouseY;
  SDL_GetMouseState(&mouseX, &mouseY);
  int playerScreenX =
      player->getGame()->getRenderer()->getEntityRenderLocation(player, true).x;
  int playerScreenY =
      player->getGame()->getRenderer()->getEntityRenderLocation(player, true).y;
  double relX = mouseX - playerScreenX;
  double relY = mouseY - playerScreenY;

  double rad = atan(relY / relX);
  double degree = rad * (180.0 / M_PI);

  if (degree == 0) {
    if (relX >= 0)
      player->setRotation(0);
    else if (relX < 0)
      player->setRotation(180);
  } else {
    if (relX < 0) {
      player->setRotation(degree + 180);
    } else {
      player->setRotation(degree);
    }
  }
}

