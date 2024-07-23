#include <SDL2/SDL_mixer.h>
class DEAD_SoundDirector {
public:
  DEAD_SoundDirector();
  ~DEAD_SoundDirector();
  void playYouDiedSound();
private:
  Mix_Chunk* youDiedSound;
};
