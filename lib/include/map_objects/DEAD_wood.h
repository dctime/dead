#include "DEAD_map_object_base.h"

class DEAD_Wood : public DEAD_MapObjectBase {
public:
  DEAD_Wood(DEAD_Map::MapLocation loc); 
  char getChar() override;
  bool isPlayerCollidable() override;
  bool isZombieCollidable() override;
  SDL_Rect getTextureRect() override;
};
