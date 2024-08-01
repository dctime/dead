#include "DEAD_multitexture_object_base.h"
#include <SDL2/SDL_rect.h>

class DEAD_Door : public DEAD_MultitextureObjectBase {
public:
  DEAD_Door(DEAD_Map::MapLocation loc); 
  char getChar() override;
  bool isPlayerCollidable() override;
  bool isZombieCollidable() override;
  std::vector<SDL_Rect> getTextureRects() override;
  void openDoor();
private:
  bool isOpen;
  std::vector<SDL_Rect> closedTextureRects;
  std::vector<SDL_Rect> openTextureRects;
};
