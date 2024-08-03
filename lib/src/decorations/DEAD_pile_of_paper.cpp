#include "decorations/DEAD_decoration_base.h"
#include <decorations/DEAD_pile_of_paper.h>

DEAD_PileOfPaper::DEAD_PileOfPaper(DEAD_Map::MapLocation loc) 
  : DEAD_DecorationBase(loc, 0.5, 0.5) {
}

SDL_Rect DEAD_PileOfPaper::getTextureRect() {
  return {.x=0, .y=0, .w=100, .h=100};
}
