#include <DEAD_player.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_scancode.h>
#include <cmath>
#include <guns/DEAD_pistol.h>
#include <DEAD_controllable_player.h>
#include <DEAD_game.h>
#include <iostream>
#include <memory>

DEAD_ControllablePlayer::DEAD_ControllablePlayer(std::shared_ptr<DEAD_Game> game)
    : DEAD_Player::DEAD_Player(game), baseSpeed(0.01 * DEAD_Game::PLAYER_MOVEMENT_DELAY / 10) {
}

DEAD_ControllablePlayer::~DEAD_ControllablePlayer() {}

void DEAD_ControllablePlayer::setGame(std::shared_ptr<DEAD_Game> game) {
  this->game = game;
  this->game->setPlayer(std::dynamic_pointer_cast<DEAD_ControllablePlayer>(shared_from_this()));
}

void DEAD_ControllablePlayer::playerEvents(SDL_Event event) {

  switch (event.type) {
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_f:
      SDL_Log("[Controllable Player] use");
      this->pickupOrDrop();
      break;
    case SDLK_g:
      SDL_Log("Summon Pistol");
      this->summonPistol();
      break;
    case SDLK_v:
      this->getGame()->getMap()->getMapSpawner()->randomSpawnAZombie();
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
  std::shared_ptr<DEAD_ControllablePlayer> shared_from_this =
      std::static_pointer_cast<DEAD_ControllablePlayer>(
          DEAD_Entity::shared_from_this());
  int playerScreenX = this->getGame()
                          ->getRenderer()
                          ->getEntityRenderLocation(shared_from_this, true)
                          .x;
  int playerScreenY = this->getGame()
                          ->getRenderer()
                          ->getEntityRenderLocation(shared_from_this, true)
                          .y;
  double relX = mouseX - playerScreenX;
  double relY = mouseY - playerScreenY;

  double rad = atan(relY / relX);
  double degree = rad * (180.0 / M_PI);

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
  bool moved = false;

  if (state[SDL_SCANCODE_W]) {
    if ((int)this->getPos().y != (int)(this->getPos().y-moveTickDistance)) {
      moved = true;
    }

    this->move(0, -moveTickDistance);
  }

  if (state[SDL_SCANCODE_S]) {
    if ((int)this->getPos().y != (int)(this->getPos().y+moveTickDistance)) {
      moved = true;
    }

    this->move(0, moveTickDistance);
  }

  if (state[SDL_SCANCODE_A]) {
    if ((int)this->getPos().x != (int)(this->getPos().x-moveTickDistance)) {
      moved = true;
    }

    this->move(-moveTickDistance, 0);
  }

  if (state[SDL_SCANCODE_D]) {
    if ((int)this->getPos().x != (int)(this->getPos().x+moveTickDistance)) {
      moved = true;
    }
    this->move(moveTickDistance, 0);
  }
  
  if (moved) {
    std::cout << "Moved Update Path finding" << std::endl;
    this->getGame()->getZombieDirector()->updateHeatMapValue();
    this->getGame()->getZombieDirector()->updateZombieMapVector();
  } 
  
}
