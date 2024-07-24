#include "ui/DEAD_ui.h"
#include <memory>
#include <vector>
class DEAD_UIDirector {
public:
  void addUI(std::shared_ptr<DEAD_UI> ui);
  std::vector<std::shared_ptr<DEAD_UI>> getUis();
private:
  std::vector<std::shared_ptr<DEAD_UI>> uis;
};
