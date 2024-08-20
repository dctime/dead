#include "DEAD_filepaths.h"
#include "DEAD_renderer.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include "subrenderers/DEAD_subrenderer_base.h"
#include <iostream>
#include <subrenderers/DEAD_explainer.h>
#include <SDL_FontCache.h>

DEAD_Explainer::DEAD_Explainer(DEAD_Renderer* renderer, DEAD_Map* map, DEAD_DecorationLayer* decorationLayer)
  : DEAD_SubRendererBase(renderer), map(map), decorationLayer(decorationLayer) {
  SDL_Color color = {.r=255, .g=255, .b=255, .a=255};
  this->font = FC_CreateFont();
  FC_LoadFont(this->font, renderer->getSDLRenderer(), DEAD_FilePaths::YOU_DIED_FONT.c_str(), 12, color, TTF_STYLE_NORMAL);

}

DEAD_Explainer::~DEAD_Explainer() {
  FC_FreeFont(this->font);
}

std::string cutTextByPixelWidth(int width, std::string objectName, FC_Font* font) {
  std::string returnString = "";
  std::string tempString = "";
  for (char c : objectName) {
    tempString += c;
    if (FC_GetWidth(font, tempString.c_str()) > width) {
      returnString += '\n';
      returnString += c;
      tempString = "";
    } else {
      returnString += c;
    }
  } 

  return returnString;
}

void DEAD_Explainer::render() {
  // render a text area and a image and notes area
  std::string objectName = "ObjectNameHelloWorldHeyYooMyNameIHaveNoName";
  std::string renderString = cutTextByPixelWidth(30, objectName, this->font);
  
  SDL_Rect rect = {.x=100, .y=100, .w=30, .h=1000};
  SDL_RenderDrawRect(this->renderer->getSDLRenderer(), &rect);
  FC_DrawAlign(this->font, this->renderer->getSDLRenderer(), 100, 100, FC_ALIGN_LEFT, renderString.c_str());
}




