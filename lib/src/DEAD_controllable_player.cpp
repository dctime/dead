#include <DEAD_game.h>
#include <DEAD_player.h>
#include <DEAD_pistol.h> 
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_scancode.h>
#include <cmath>
#include <iostream>

DEAD_ControllablePlayer::DEAD_ControllablePlayer(DEAD_Player::Position *pos)
    : DEAD_Player::DEAD_Player(pos) {}

DEAD_ControllablePlayer::~DEAD_ControllablePlayer() {}

void DEAD_ControllablePlayer::playerEvents(SDL_Event event) { 
   
  switch (event.type) {
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_f:
      SDL_Log("[Controllable Player] use");
      std::shared_ptr<DEAD_Weapon> pistol = std::make_shared<DEAD_Pistol>(this);
      this->pickupWeapon(pistol);
      break;
    }
    break;
  case SDL_MOUSEBUTTONDOWN:
    if (event.button.button == SDL_BUTTON_LEFT) {
      this->attack();
    }
  }
}

void DEAD_ControllablePlayer::handlePlayerRotation() {
  int mouseX;
  int mouseY;
  SDL_GetMouseState(&mouseX, &mouseY);
  int playerScreenX = this->getGame()->getRenderer()->getPlayerRenderLocation(this, true).x;
  int playerScreenY = this->getGame()->getRenderer()->getPlayerRenderLocation(this, true).y;
  double relX = mouseX - playerScreenX;
  double relY = mouseY - playerScreenY;
  
  double rad = atan(relY/relX);
  double degree = rad * (180.0/M_PI);

  if (degree == 0) {
    if (relX >= 0)
      this->setRotation(0);
    else if (relX < 0)
      this->setRotation(180);
  } else {
    if (relX < 0) {
      this->setRotation(degree + 180);
    } else {
      this->setRotation(degree);
    }
  }
}

void DEAD_ControllablePlayer::handleKeyState() {
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  double moveTickDistance = this->baseSpeed * this->getSpeed();
  if (state[SDL_SCANCODE_W]) {
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
