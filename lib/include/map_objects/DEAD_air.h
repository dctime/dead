#include "DEAD_map_object_base.h"

class DEAD_Air : public DEAD_MapObjectBase {
public:
  DEAD_Air(DEAD_Map::MapLocation loc);
  char getChar() override;
};
