#include "decorations/DEAD_decoration_base.h"
#include <decorations/DEAD_pile_of_paper.h>

DEAD_PileOfPaper::DEAD_PileOfPaper(DEAD_Map::MapLocation loc, double rotationAngle, bool hasItemDrops, DEAD_Game* game) 
  : DEAD_DecorationBase(loc, 1, 1, rotationAngle, 0.3, hasItemDrops, game) {
}

SDL_Rect DEAD_PileOfPaper::getTextureRect() {
  return {.x=0, .y=0, .w=100, .h=100};
}

double DEAD_PileOfPaper::destroyRequireTicks() {
  return 500;
}
