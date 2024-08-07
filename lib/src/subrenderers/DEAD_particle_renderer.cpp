#include "subrenderers/DEAD_subrenderer_base.h"
#include <subrenderers/DEAD_particle_renderer.h>
#include <memory>
#include <vector>
#include <particles/DEAD_particle_base.h>
#include <particles/DEAD_sword_attack_particle.h>

DEAD_ParticleRenderer::DEAD_ParticleRenderer(
    DEAD_Renderer* renderer)
    : DEAD_SubRendererBase(renderer) {}

void DEAD_ParticleRenderer::playSwordAttackParticle(DEAD_Map::MapLocation loc,
                                                    double angle) {
  std::shared_ptr<DEAD_ParticleBase> particle =
      std::make_shared<DEAD_SwordAttackParticle>(this->renderer, loc, angle);
  particle->play();
  this->playingParticles.insert(particle);
}

void DEAD_ParticleRenderer::render() {
  std::vector<std::shared_ptr<DEAD_ParticleBase>> readyToFreeParticles;
  for (const std::shared_ptr<DEAD_ParticleBase>& particle : this->playingParticles) {
    if (!particle->render())
      readyToFreeParticles.push_back(particle);
  }

  for (const std::shared_ptr<DEAD_ParticleBase>& readyToFreeParticle : readyToFreeParticles) {
    this->playingParticles.erase(readyToFreeParticle);
  }
}
