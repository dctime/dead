#include "DEAD_filepaths.h"
#include <DEAD_sound_director.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <random>
// 1: You Died
// 2 - 9 gun sound
DEAD_SoundDirector::DEAD_SoundDirector() 
  : youDiedSound(Mix_LoadWAV(DEAD_FilePaths::YOU_DIED_SOUND.c_str())) {
  Mix_AllocateChannels(32);
  if (this->youDiedSound == NULL) std::cout << "You Died Sound Load Failed: " << SDL_GetError() << std::endl;
  this->pistolShootSounds.push_back(Mix_LoadWAV(DEAD_FilePaths::PISTOL_SHOOT_SOUND_1.c_str()));
  this->pistolShootSounds.push_back(Mix_LoadWAV(DEAD_FilePaths::PISTOL_SHOOT_SOUND_2.c_str()));
  this->pistolShootSounds.push_back(Mix_LoadWAV(DEAD_FilePaths::PISTOL_SHOOT_SOUND_3.c_str()));
  this->pistolShootSounds.push_back(Mix_LoadWAV(DEAD_FilePaths::PISTOL_SHOOT_SOUND_4.c_str()));
}

void DEAD_SoundDirector::playYouDiedSound() {
  Mix_PlayChannel(1, this->youDiedSound, 0);
}

DEAD_SoundDirector::~DEAD_SoundDirector() {
  Mix_FreeChunk(this->youDiedSound);
  for (Mix_Chunk* pistolSound : this->pistolShootSounds) {
    Mix_FreeChunk(pistolSound);
  }
}


void DEAD_SoundDirector::playPistolShootSound() {
  std::random_device rd;
  std::uniform_int_distribution<int> dis(0, this->pistolShootSounds.size()-1);
  for (int channelCounter = 2; channelCounter <= 9; channelCounter++) {
    if (Mix_Playing(channelCounter)) continue;
    Mix_PlayChannel(channelCounter, this->pistolShootSounds.at(dis(rd)), 0);
    break;
  }
}
