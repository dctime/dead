#include "DEAD_map_object_base.h"
#include "DEAD_player_memorable_object_interface.h"

class DEAD_Wood : public DEAD_MapObjectBase, public DEAD_IPlayerMemoriableObject {
public:
  DEAD_Wood(DEAD_Map::MapLocation loc); 
  char getChar() override;
  bool isPlayerCollidable() override;
  bool isZombieCollidable() override;
  SDL_Rect getTextureRect() override;
  bool isVisible() override;
  void setToVisible() override;
private:
  bool visible;
};
