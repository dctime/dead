#include "DEAD_subrenderer_base.h"
#include "../DEAD_map.h"
#include "../DEAD_decoration_layer.h"
#include "../SDL_FontCache.h"

class DEAD_Explainer : public DEAD_SubRendererBase {
public:
  DEAD_Explainer(DEAD_Renderer* renderer, DEAD_Map* map, DEAD_DecorationLayer* decorationLayer);
  virtual ~DEAD_Explainer();
  void render() override;
private:
  DEAD_Map* map;
  DEAD_DecorationLayer* decorationLayer;
  FC_Font* noteFont;
  FC_Font* nameFont;
  SDL_Texture* mapObjectTexture;
  SDL_Texture* decorationTexture;
  char* noteTextTemp;
};
