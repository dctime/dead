#pragma once
#include <memory>
#include <set>
#include "../particles/DEAD_particle_base.h"

class DEAD_Renderer;

class DEAD_ParticleRenderer {
public:
  DEAD_ParticleRenderer(DEAD_Renderer* renderer);
  void playSwordAttackParticle(DEAD_Map::MapLocation loc, double angle);
  void render();
private:
  DEAD_Renderer* renderer;
  std::set<std::shared_ptr<DEAD_ParticleBase>> playingParticles;
};
