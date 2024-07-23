#include <SDL2/SDL_mixer.h>
#include <vector>
class DEAD_SoundDirector {
public:
  DEAD_SoundDirector();
  ~DEAD_SoundDirector();
  void playYouDiedSound();
  void playPistolShootSound();
private:
  Mix_Chunk* youDiedSound;
  std::vector<Mix_Chunk*> pistolShootSounds;
  
};
