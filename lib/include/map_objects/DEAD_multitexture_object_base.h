#include "DEAD_map_object_base.h"

enum DEAD_MapObjectDirection {
  HORIZONTAL,
  VERTICAL
};

class DEAD_MultitextureObjectBase : public DEAD_MapObjectBase {
public:
  DEAD_MultitextureObjectBase(DEAD_Map::MapLocation loc);
  virtual ~DEAD_MultitextureObjectBase();
  virtual char getChar() override = 0;
  virtual bool isPlayerCollidable() override = 0;
  virtual bool isZombieCollidable() override = 0;
  SDL_Rect getTextureRect() override final;
  virtual std::vector<SDL_Rect> getTextureRects() = 0;
  DEAD_MapObjectDirection getDirection();
  void setDirection(DEAD_MapObjectDirection direction);
private:
  int currentTextureIndex;
  DEAD_MapObjectDirection direction;
};
