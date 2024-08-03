#pragma once
#include "DEAD_ui_renderer.h"
#include "../DEAD_decoration_layer.h"
#include <SDL2/SDL_render.h>
#include "../DEAD_renderer.h"

class DEAD_DecorationRenderer : public DEAD_SubRendererBase {
public:
  DEAD_DecorationRenderer(DEAD_Renderer* renderer, DEAD_DecorationLayer* layer);
  ~DEAD_DecorationRenderer();
  void render() override;
  ScreenLocation getDecorationRenderLocation(DEAD_DecorationBase* deco);
private:
  DEAD_DecorationLayer* layer;
  SDL_Texture* decorationTexture;
};
