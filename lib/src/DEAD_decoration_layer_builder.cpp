#include "DEAD_decoration_layer.h"
#include "DEAD_functions.h"
#include <DEAD_decoration_layer_builder.h>
#include <DEAD_map.h>
#include <decorations/DEAD_pile_of_paper.h>
#include <iostream>
#include <memory>
#include <random>

DEAD_DecorationLayerBuilder::DEAD_DecorationLayerBuilder()
    : decorationLayer(std::make_unique<DEAD_DecorationLayer>()) {
  DEAD_Map::MapLocation loc = {.x = 4.5, .y = 28.5};
  this->addPileOfPaperCluster(loc, 0.5, 3, 3);
}

void DEAD_DecorationLayerBuilder::build(
    std::unique_ptr<DEAD_DecorationLayer> &layer) {
  layer = std::move(this->decorationLayer);
}

void DEAD_DecorationLayerBuilder::addPileOfPaperCluster(
    DEAD_Map::MapLocation loc, double sigma, double maxWidth,
    double maxHeight) {
  std::normal_distribution<double> disX(loc.x, sigma);
  std::normal_distribution<double> disY(loc.y, sigma);
  std::uniform_real_distribution<double> rotationAngle(0, 360);
  for (int i = 0; i < 10; i++) {
    std::random_device rd;
    DEAD_Map::MapLocation tempLoc;
    tempLoc.x = DEAD_Functions::boundNumber(disX(rd), loc.x-maxWidth/2.0, loc.x+maxWidth/2.0);
    tempLoc.y = DEAD_Functions::boundNumber(disY(rd), loc.y-maxHeight/2.0, loc.y+maxHeight/2.0);
    std::cout << tempLoc.x << ", ";
    std::cout << tempLoc.y << std::endl;
    this->decorationLayer->decorations.push_back(std::make_unique<DEAD_PileOfPaper>(tempLoc, rotationAngle(rd)));
  }
}
