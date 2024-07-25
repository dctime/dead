#include <DEAD_particle_renderer.h>
#include <iostream>
#include <memory>
#include <particles/DEAD_particle_base.h>
#include <particles/DEAD_sword_attack_particle.h>

DEAD_ParticleRenderer::DEAD_ParticleRenderer(
    std::shared_ptr<DEAD_Renderer> renderer)
    : renderer(renderer) {}

void DEAD_ParticleRenderer::playSwordAttackParticle(DEAD_Map::MapLocation loc,
                                                    double angle) {
  std::shared_ptr<DEAD_ParticleBase> particle =
      std::make_shared<DEAD_SwordAttackParticle>(this->renderer, loc, angle);
  particle->play();
  this->playingParticles.insert(particle);
}

void DEAD_ParticleRenderer::render() {
  for (std::shared_ptr<DEAD_ParticleBase> particle : this->playingParticles) {
    if (!particle->render())
      this->playingParticles.erase(particle);
  }
}
