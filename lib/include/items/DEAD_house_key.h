#include "../DEAD_item.h"

class DEAD_HouseKey : public DEAD_Item {
public:
  DEAD_HouseKey(DEAD_Player* owner);
  SDL_Rect getTextureRect() override;
  SDL_Rect getItemTextureRect() override;
  bool use() override;

};
