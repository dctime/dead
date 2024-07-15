#include "DEAD_map_object_base.h"

class DEAD_Stone : public DEAD_MapObjectBase {
public:
  DEAD_Stone();
  char getChar() override;
};
