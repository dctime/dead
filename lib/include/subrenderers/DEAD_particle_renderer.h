#pragma once
#include <memory>
#include <set>
#include "../particles/DEAD_particle_base.h"
#include "DEAD_ui_renderer.h"

class DEAD_Renderer;

class DEAD_ParticleRenderer : public DEAD_SubRendererBase {
public:
  DEAD_ParticleRenderer(DEAD_Renderer* renderer);
  void playSwordAttackParticle(DEAD_Map::MapLocation loc, double angle);
  void render() override;
private:
  std::set<std::shared_ptr<DEAD_ParticleBase>> playingParticles;
};
