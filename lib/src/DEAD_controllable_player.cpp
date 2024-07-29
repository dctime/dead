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
#include <weapons/DEAD_bat.h>
#include <iostream>
#include <memory>
#include <DEAD_particle_renderer.h>

DEAD_ControllablePlayer::DEAD_ControllablePlayer(std::shared_ptr<DEAD_Game> game)
    : DEAD_Player::DEAD_Player(game), baseSpeed(0.01 * DEAD_Game::MAIN_LOOP_DELAY / 10) {
}

DEAD_ControllablePlayer::~DEAD_ControllablePlayer() {}

void DEAD_ControllablePlayer::setGame(std::shared_ptr<DEAD_Game> game) {
  this->game = game;
  }

void DEAD_ControllablePlayer::playerEvents(SDL_Event event) {

  DEAD_Map::MapLocation loc = {.x=5.5, .y=5.5};
  switch (event.type) {
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_f:
      SDL_Log("[Controllable Player] use");
      this->pickupOrDrop();
      break;
    case SDLK_g:
      SDL_Log("Summon Weapon");
      this->summonWeapon<DEAD_Pistol>();
      break;
    case SDLK_v:
      std::cout << "Zombie count: " << this->game->getZombieDirector()->getZombies().size() << std::endl;
      break;
    case SDLK_r:
      this->reloadGun();
    }

    break;
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

  int mouseX;
  int mouseY;
  if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON_LMASK) {
    this->attack();
  }

  if (state[SDL_SCANCODE_W]) {
    this->move(0, -moveTickDistance);
  }

  if (state[SDL_SCANCODE_S]) {

    this->move(0, moveTickDistance);
  }

  if (state[SDL_SCANCODE_A]) {
    this->move(-moveTickDistance, 0);
  }

  if (state[SDL_SCANCODE_D]) {
    this->move(moveTickDistance, 0);
  }
}
