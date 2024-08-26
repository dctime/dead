#include <DEAD_controllable_player.h>
#include <DEAD_game.h>
#include <DEAD_player.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_timer.h>
#include <cmath>
#include <iostream>
#include <items/weapons/DEAD_bat.h>
#include <items/weapons/guns/DEAD_pistol.h>
#include <memory>
#include <player_input_method/DEAD_player_input_method_2d.h>
#include <player_input_method/DEAD_player_input_method_3d.h>
#include <subrenderers/DEAD_particle_renderer.h>

DEAD_ControllablePlayer::DEAD_ControllablePlayer(DEAD_Game *game,
                                                 std::string playerName)
    : DEAD_Player::DEAD_Player(game),
      baseSpeed(0.01 * DEAD_Game::MAIN_LOOP_DELAY / 10) {
  this->setEntityName(playerName);
  this->inputMethod =
      std::make_unique<DEAD_PlayerInputMethod3D>(this, this->baseSpeed);
}

DEAD_ControllablePlayer::~DEAD_ControllablePlayer() {}

void DEAD_ControllablePlayer::setGame(DEAD_Game *game) { this->game = game; }

void DEAD_ControllablePlayer::playerEvents(SDL_Event event) {

  DEAD_Map::MapLocation loc = {.x = 5.5, .y = 5.5};
  switch (event.type) {
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_q:
      SDL_Log("[Controllable Player] pickup or drop");
      this->pickupOrDrop();
      break;
    case SDLK_f:
      this->useItem();
      break;
    case SDLK_v:
      std::cout << "Zombie count: "
                << this->game->getZombieDirector()->getZombies().size()
                << std::endl;
      break;
    case SDLK_r:
      this->reloadGun();
    }
    break;
  case SDL_MOUSEWHEEL:
    if (event.wheel.y > 0) {
      std::cout << "Scroll UP" << std::endl;
      this->getInventory()->previousItemHotbar();
    } else if (event.wheel.y < 0) {
      std::cout << "Scroll Down" << std::endl;
      this->getInventory()->nextItemHotbar();
    }

    break;
  }
}

// TODO: Make player input method class

void DEAD_ControllablePlayer::handlePlayerRotation() {
  this->inputMethod->handlePlayerRotation();
}

void DEAD_ControllablePlayer::handleKeyState() {
  this->isPressingUseKey = false;

  const Uint8 *state = SDL_GetKeyboardState(NULL);

  int mouseX;
  int mouseY;

  if (state[SDL_SCANCODE_F] && this->holdItem == nullptr) {
    this->isPressingUseKey = true;
    this->interactWithDecoration(this->pressTimeTicks);
  }

  if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON_LMASK) {
    this->attack();
  }

  this->updatePressUseTimeTicks();

  this->inputMethod->handleKeyState();
}

void DEAD_ControllablePlayer::updatePressUseTimeTicks() {
  if (!this->isPressingUseKey)
    this->lastTimePressTicks = SDL_GetTicks64();
  this->pressTimeTicks = SDL_GetTicks64() - this->lastTimePressTicks;
}

bool DEAD_ControllablePlayer::getIsPressingUseKey() {
  return this->isPressingUseKey;
}

void DEAD_ControllablePlayer::resetLastTimePressTicks() {
  this->lastTimePressTicks = SDL_GetTicks64();
}

void switchInputMethodTo3D() {}

void switchInputMethodTo2D() {}
