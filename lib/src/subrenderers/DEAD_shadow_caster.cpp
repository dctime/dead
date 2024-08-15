#include "subrenderers/DEAD_subrenderer_base.h"
#include <subrenderers/DEAD_shadow_caster.h>
#include <DEAD_renderer.h>
#include <DEAD_game.h>
#include <iostream>

DEAD_ShadowCaster::DEAD_ShadowCaster(DEAD_Renderer* renderer)
  : DEAD_SubRendererBase(renderer), map(renderer->getGame()->getMap()) {
}

void DEAD_ShadowCaster::render() {
}


