#pragma once
#include "../DEAD_map.h"
#include "DEAD_label_renderer.h"
#include "DEAD_subrenderer_base.h"
#include <memory>

class DEAD_ShadowCaster : public DEAD_SubRendererBase {
public:
  
  DEAD_ShadowCaster(DEAD_Renderer *renderer);

  void render() override;
  bool isMouseInLineOfSight();

private:
  DEAD_Map *map;
  std::unique_ptr<DEAD_LabelRenderer> labelRenderer;
  
  SDL_Texture *shadowMask;
  SDL_Texture *shadowOutwardMask;
  bool mouseInLineOfSight;
  
};
