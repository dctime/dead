#include <SDL2/SDL.h>

class DEAD_Bullets {
public:
  virtual SDL_Rect getBulletTextureRect() = 0;
private:
};
