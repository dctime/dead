#include "DEAD_particle_base.h"
#include "../DEAD_map.h"
#include <SDL2/SDL_rect.h>

class DEAD_SwordAttackParticle : public DEAD_ParticleBase {
public:
  DEAD_SwordAttackParticle(std::shared_ptr<DEAD_Renderer> renderer, DEAD_Map::MapLocation loc, double angle); 
  void play() override;
  bool render() override;
private:
  int startTicks;
  const int TICKS_LENGTH;
  double angle;
  DEAD_Map::MapLocation loc;
  SDL_Rect targetRenderRect;
};
