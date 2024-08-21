#include "../DEAD_decoration_layer.h"
#include "../DEAD_map.h"
#include "../SDL_FontCache.h"
#include "../DEAD_item_drop.h"
#include "../DEAD_item_drop_layer.h"
#include "DEAD_subrenderer_base.h"
#include <memory>

class DEAD_Explainer : public DEAD_SubRendererBase {
public:
  void renderMapObjectExplain(int imageSize, int noteSize, int boarderSize,
                              DEAD_MapObjectBase *object);
  void renderDecorationExplain(int imageSize, int noteSize, int boarderSize,
                               DEAD_DecorationBase *object);
  void renderItemDropExplain(int imageSize, int noteSize, int boarderSize, std::shared_ptr<DEAD_ItemDrop>& itemDrop);
  void renderExplain(int imageSize, int noteSize, int boarderSize,
                     std::string nameText, std::string noteText,
                     SDL_Rect textureRect, SDL_Texture *texture);
  DEAD_Explainer(DEAD_Renderer *renderer, DEAD_Map *map,
                 DEAD_DecorationLayer *decorationLayer, DEAD_ItemDropLayer* itemDropLayer);
  virtual ~DEAD_Explainer();
  void render() override;

private:
  DEAD_Map *map;
  DEAD_DecorationLayer *decorationLayer;
  DEAD_ItemDropLayer* itemDropLayer;
  FC_Font *noteFont;
  FC_Font *nameFont;
  SDL_Texture *mapObjectTexture;
  SDL_Texture *decorationTexture;
  char *noteTextTemp;
};
