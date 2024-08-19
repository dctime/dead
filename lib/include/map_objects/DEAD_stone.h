#include "DEAD_map_object_base.h"
#include "DEAD_player_memoriable_object.h"
#include <memory>

class DEAD_Stone : public DEAD_MapObjectBase, public DEAD_IPlayerMemoriableObject {
public:
  DEAD_Stone(DEAD_Map::MapLocation loc);
  char getChar() override;
  bool isPlayerCollidable() override;
  bool isZombieCollidable() override;
  SDL_Rect getTextureRect() override;
  DEAD_PlayerMemoriableManager * getMemoryManager() override;
private:
  std::unique_ptr<DEAD_PlayerMemoriableManager> memoryManager;
};
