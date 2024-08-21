#include "DEAD_map_object_base.h"

class DEAD_Road : public DEAD_MapObjectBase {
public:
  DEAD_Road(DEAD_Map::MapLocation loc);
  char getChar() override;
  bool isPlayerCollidable() override;
  bool isZombieCollidable() override;
  SDL_Rect getTextureRect() override;
  std::string getName() override;
  std::string getNote() override;
};
