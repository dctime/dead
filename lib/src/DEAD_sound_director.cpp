#include "DEAD_filepaths.h"
#include <DEAD_sound_director.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

DEAD_SoundDirector::DEAD_SoundDirector() 
  : youDiedSound(Mix_LoadWAV(DEAD_FilePaths::YOU_DIED_SOUND.c_str())) {
  if (this->youDiedSound == NULL) std::cout << "You Died Sound Load Failed: " << SDL_GetError() << std::endl;
}

void DEAD_SoundDirector::playYouDiedSound() {
  Mix_PlayChannel(-1, this->youDiedSound, 0);
}

DEAD_SoundDirector::~DEAD_SoundDirector() {
  Mix_FreeChunk(this->youDiedSound);
}
