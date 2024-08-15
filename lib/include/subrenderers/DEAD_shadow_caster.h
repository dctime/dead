#pragma once
#include "../DEAD_map.h"
#include "DEAD_subrenderer_base.h"

class DEAD_ShadowCaster : public DEAD_SubRendererBase {
public:
  DEAD_ShadowCaster(DEAD_Renderer* renderer); 
  void render() override;
private:
  DEAD_Map* map;
  
};
