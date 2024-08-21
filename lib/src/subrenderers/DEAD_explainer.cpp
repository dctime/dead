#include "DEAD_filepaths.h"
#include "DEAD_renderer.h"
#include "SDL_mouse.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include "map_objects/DEAD_map_object_base.h"
#include "map_objects/DEAD_player_memoriable_object.h"
#include "subrenderers/DEAD_subrenderer_base.h"
#include <DEAD_game.h>
#include <SDL_FontCache.h>
#include <iostream>
#include <memory>
#include <subrenderers/DEAD_explainer.h>
#include <subrenderers/DEAD_shadow_caster.h>

DEAD_Explainer::DEAD_Explainer(DEAD_Renderer *renderer, DEAD_Map *map,
                               DEAD_DecorationLayer *decorationLayer,
                               DEAD_ItemDropLayer *itemDropLayer)
    : DEAD_SubRendererBase(renderer), map(map),
      decorationLayer(decorationLayer), itemDropLayer(itemDropLayer) {
  SDL_Color color = {.r = 255, .g = 255, .b = 255, .a = 255};
  this->nameFont = FC_CreateFont();
  this->noteFont = FC_CreateFont();
  FC_LoadFont(this->noteFont, renderer->getSDLRenderer(),
              DEAD_FilePaths::YOU_DIED_FONT.c_str(), 12, color,
              TTF_STYLE_NORMAL);
  FC_LoadFont(this->nameFont, renderer->getSDLRenderer(),
              DEAD_FilePaths::YOU_DIED_FONT.c_str(), 24, color,
              TTF_STYLE_NORMAL);
  this->mapObjectTexture = renderer->getMapObjectTexture();
  this->decorationTexture = renderer->getDecorationTexture();
  this->noteTextTemp = new char[1000];
}

DEAD_Explainer::~DEAD_Explainer() {
  FC_FreeFont(this->nameFont);
  FC_FreeFont(this->noteFont);
  delete this->noteTextTemp;
}

void DEAD_Explainer::render() {
  // render a text area and a image and notes area
  int imageSize = 30;
  int noteSize = 200;
  int boarderSize = 10;
  ScreenLocation mouseScreenLocation;
  SDL_GetMouseState(&mouseScreenLocation.x, &mouseScreenLocation.y);
  DEAD_Map::MapLocation mousePointingMapLocation =
      this->renderer->getMapLocFromScreenLoc(mouseScreenLocation);

  std::shared_ptr<DEAD_ItemDrop> itemDrop;
  this->itemDropLayer->getNearItemDrop(mousePointingMapLocation, 0.3, itemDrop);

  if (itemDrop != nullptr && this->renderer->getShadowCaster()->isMouseInLineOfSight()) {
    this->renderItemDropExplain(imageSize, noteSize, boarderSize, itemDrop);
    return;
  }

  DEAD_DecorationBase *decoObject =
      this->decorationLayer->getFirstDecorationByLoc(mousePointingMapLocation);

  if (decoObject != nullptr && this->renderer->getShadowCaster()->isMouseInLineOfSight()) {
    this->renderDecorationExplain(imageSize, noteSize, boarderSize, decoObject);
    return;
  }

  DEAD_MapObjectBase *object = this->map->getMapObject(
      (int)mousePointingMapLocation.x, (int)mousePointingMapLocation.y);
  DEAD_IPlayerMemoriableObject *memoriableObject = this->map->getPlayerMemoriableObject((int)mousePointingMapLocation.x, (int)mousePointingMapLocation.y);
  if (object != nullptr && 
    (memoriableObject == nullptr && this->renderer->getShadowCaster()->isMouseInLineOfSight() ||
    (memoriableObject != nullptr && memoriableObject->getMemoryManager()->isVisible()))) {
    this->renderMapObjectExplain(imageSize, noteSize, boarderSize, object);
    return;
  }
}

void DEAD_Explainer::renderItemDropExplain(
    int imageSize, int noteSize, int boarderSize,
    std::shared_ptr<DEAD_ItemDrop> &itemDrop) {
  renderExplain(imageSize, noteSize, boarderSize,
                itemDrop->getName(), itemDrop->getNote(),
                itemDrop->getItem()->getItemTextureRect(),
                this->renderer->getItemTexture());
}

void DEAD_Explainer::renderDecorationExplain(int imageSize, int noteSize,
                                             int boarderSize,
                                             DEAD_DecorationBase *object) {
  renderExplain(imageSize, noteSize, boarderSize, object->getName(),
                object->getNote(), object->getTextureRect(),
                this->decorationTexture);
}

void DEAD_Explainer::renderMapObjectExplain(int imageSize, int noteSize,
                                            int boarderSize,
                                            DEAD_MapObjectBase *object) {
  renderExplain(imageSize, noteSize, boarderSize, object->getName(),
                object->getNote(), object->getTextureRect(),
                this->mapObjectTexture);
}

void DEAD_Explainer::renderExplain(int imageSize, int noteSize, int boarderSize,
                                   std::string nameText, std::string noteText,
                                   SDL_Rect textureRect, SDL_Texture *texture) {

  int nameTextWidth =
      imageSize + boarderSize + FC_GetWidth(this->nameFont, nameText.c_str());
  int nameTextHeight = FC_GetHeight(this->nameFont, nameText.c_str());

  int maxTextWidth = 0;
  if (noteSize > maxTextWidth) {
    maxTextWidth = noteSize;
  }
  if (nameTextWidth > maxTextWidth) {
    maxTextWidth = nameTextWidth;
  }

  int x = (int)(this->renderer->getGame()->SCREEN_WIDTH / 2) -
          (int)(maxTextWidth / 2);

  SDL_Rect renderRect = {.x = x, .y = 5, .w = imageSize, .h = imageSize};
  SDL_RenderCopy(this->renderer->getSDLRenderer(), texture, &textureRect,
                 &renderRect);
  FC_Draw(this->nameFont, this->renderer->getSDLRenderer(),
          x + imageSize + boarderSize, (int)(boarderSize / 2),
          nameText.c_str());

  FC_GetWrappedText(this->noteFont, this->noteTextTemp, 1000, noteSize,
                    noteText.c_str());
  // noteText = cutTextByPixelWidth(200, noteText, this->noteFont);

  FC_DrawAlign(this->noteFont, this->renderer->getSDLRenderer(), x,
               imageSize + boarderSize, FC_ALIGN_LEFT, this->noteTextTemp);
}
