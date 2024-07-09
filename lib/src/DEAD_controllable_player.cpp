#include "DEAD_player.h"
#include <DEAD_controllable_player.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_log.h>

DEAD_ControllablePlayer::DEAD_ControllablePlayer(DEAD_Player::Position* pos) 
  : DEAD_Player::DEAD_Player(pos) {
    
}

DEAD_ControllablePlayer::~DEAD_ControllablePlayer() {}

void DEAD_ControllablePlayer::playerEvents(SDL_Event event) {
  SDL_Log("[Controllable Player] toggle events");  
}
