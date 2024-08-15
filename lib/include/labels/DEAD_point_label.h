#include "DEAD_label_base.h"
#include "../DEAD_renderer.h"

class DEAD_PointLabel : public DEAD_LabelBase {
public:
  DEAD_PointLabel(double mapX, double mapY, double mapRadius, DEAD_Renderer* renderer);
  ~DEAD_PointLabel();
  void render() override;

private:
  double mapRadius;

};
