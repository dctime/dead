#include "DEAD_map_object_base.h"

class DEAD_Stone : public DEAD_MapObjectBase {
public:
  DEAD_Stone(DEAD_Map::MapLocation loc);
  char getChar() override;
  bool isPlayerCollidable() override;
};
