#include "DEAD_map_object_base.h"

class DEAD_Point : public DEAD_MapObjectBase {
public:
  DEAD_Point(DEAD_Map::MapLocation loc);
  char getChar() override;
  bool isPlayerCollidable() override;
  bool isZombieCollidable() override;
};
