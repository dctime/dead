#include "subrenderers/DEAD_subrenderer_base.h"
#include <subrenderers/DEAD_shadow_caster.h>
#include <DEAD_renderer.h>
#include <DEAD_game.h>
#include <iostream>

DEAD_ShadowCaster::DEAD_ShadowCaster(DEAD_Renderer* renderer)
  : DEAD_SubRendererBase(renderer), map(renderer->getGame()->getMap()) {
}

void DEAD_ShadowCaster::render() {
  ScreenLocation testLoc = this->renderer->getPointRenderLocation(1, 1);
  // make a label renderer
  // render a circle label
  // find all points sorted in angle
  // find all edges
  // find a way to render a polygon mask
  // complete all stuff
}


