#include "DEAD_decoration_base.h"
#include "../DEAD_map.h"

class DEAD_PileOfPaper : public DEAD_DecorationBase {
public:
  DEAD_PileOfPaper(DEAD_Map::MapLocation loc, double rotationAngle);
  SDL_Rect getTextureRect() override;
private:
};
