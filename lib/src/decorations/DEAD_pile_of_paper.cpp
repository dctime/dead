#include "decorations/DEAD_decoration_base.h"
#include <decorations/DEAD_pile_of_paper.h>

DEAD_PileOfPaper::DEAD_PileOfPaper(DEAD_Map::MapLocation loc, double rotationAngle) 
  : DEAD_DecorationBase(loc, 1, 1, rotationAngle) {
}

SDL_Rect DEAD_PileOfPaper::getTextureRect() {
  return {.x=0, .y=0, .w=100, .h=100};
}
