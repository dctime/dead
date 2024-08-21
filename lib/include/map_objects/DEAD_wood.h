#include "DEAD_map_object_base.h"
#include <memory>

class DEAD_Wood : public DEAD_MapObjectBase, public DEAD_IPlayerMemoriableObject {
public:
  DEAD_Wood(DEAD_Map::MapLocation loc); 
  char getChar() override;
  bool isPlayerCollidable() override;
  bool isZombieCollidable() override;
  SDL_Rect getTextureRect() override;
  std::string getName() override;
  std::string getNote() override;
  DEAD_PlayerMemoriableManager * getMemoryManager() override;
private:
  std::unique_ptr<DEAD_PlayerMemoriableManager> memoryMamanger;
};
