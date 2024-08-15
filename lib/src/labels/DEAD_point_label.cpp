#include "DEAD_renderer.h"
#include <labels/DEAD_point_label.h>

DEAD_PointLabel::DEAD_PointLabel(double mapX, double mapY, double mapRadius, DEAD_Renderer* renderer)
  : DEAD_LabelBase(mapX, mapY, renderer), mapRadius(mapRadius) {
}

DEAD_PointLabel::~DEAD_PointLabel() {}

void DEAD_PointLabel::render() {
  ScreenLocation renderLeftUpLoc = this->getRenderer()->getPointRenderLocation(this->getMidLoc().x-this->mapRadius/2, this->getMidLoc().y-this->mapRadius/2);

  SDL_Rect textureRect = {.x=0, .y=0, .w=100, .h=100};
  SDL_Rect renderRect = {
      .x=(int)(renderLeftUpLoc.x),
      .y=(int)(renderLeftUpLoc.y),
      .w=(int)(this->mapRadius*this->getRenderer()->getRenderBlockSize()),
      .h=(int)(this->mapRadius*this->getRenderer()->getRenderBlockSize())
  };
  SDL_RenderCopy(this->getRenderer()->getSDLRenderer(), this->getLabelTexture(), &textureRect, &renderRect); 
}
