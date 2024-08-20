#include "DEAD_filepaths.h"
#include "DEAD_renderer.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include "subrenderers/DEAD_subrenderer_base.h"
#include <iostream>
#include <subrenderers/DEAD_explainer.h>
#include <SDL_FontCache.h>
#include <DEAD_game.h>

DEAD_Explainer::DEAD_Explainer(DEAD_Renderer* renderer, DEAD_Map* map, DEAD_DecorationLayer* decorationLayer)
  : DEAD_SubRendererBase(renderer), map(map), decorationLayer(decorationLayer) {
  SDL_Color color = {.r=255, .g=255, .b=255, .a=255};
  this->nameFont = FC_CreateFont();
  this->noteFont = FC_CreateFont();
  FC_LoadFont(this->noteFont, renderer->getSDLRenderer(), DEAD_FilePaths::YOU_DIED_FONT.c_str(), 12, color, TTF_STYLE_NORMAL);
  FC_LoadFont(this->nameFont, renderer->getSDLRenderer(), DEAD_FilePaths::YOU_DIED_FONT.c_str(), 24, color, TTF_STYLE_NORMAL);
  this->mapObjectTexture = renderer->getMapObjectTexture();
  this->noteTextTemp = new char[1000];
}

DEAD_Explainer::~DEAD_Explainer() {
  FC_FreeFont(this->nameFont);
  FC_FreeFont(this->noteFont);
  delete this->noteTextTemp;
}


void DEAD_Explainer::render() {
  // render a text area and a image and notes area
  std::string nameText = "Stone Block"; 
  std::string noteText = "Well Its Just a Simple Block. These are some text. Note that a stone is just a stone, and there is nothing else";

  int imageSize = 30;
  int noteSize = 200;
  int boarderSize = 10;

  int nameTextWidth = imageSize + boarderSize + FC_GetWidth(this->nameFont, nameText.c_str());
  int nameTextHeight = FC_GetHeight(this->nameFont, nameText.c_str());

  int maxTextWidth = 0;
  if (noteSize > maxTextWidth) { maxTextWidth = noteSize; }
  if (nameTextWidth > maxTextWidth) { maxTextWidth = nameTextWidth; }

  int x = (int)(this->renderer->getGame()->SCREEN_WIDTH/2) - (int)(maxTextWidth/2);
  
  SDL_Rect testRect = {.x=0, .y=0, .w=100, .h=100};
  SDL_Rect renderRect = {.x=x, .y=5, .w=imageSize, .h=imageSize};

  SDL_RenderCopy(this->renderer->getSDLRenderer(), this->mapObjectTexture, &testRect, &renderRect);
  FC_Draw(this->nameFont, this->renderer->getSDLRenderer(), x+imageSize+boarderSize, (int)(boarderSize/2), nameText.c_str());

  FC_GetWrappedText(this->noteFont, this->noteTextTemp, 1000, noteSize, noteText.c_str());
  // noteText = cutTextByPixelWidth(200, noteText, this->noteFont);
  
  FC_DrawAlign(this->noteFont, this->renderer->getSDLRenderer(), x, imageSize+boarderSize, FC_ALIGN_LEFT, this->noteTextTemp);
}




