#include <DEAD_ui_director.h>
#include <memory>
void DEAD_UIDirector::addUI(std::shared_ptr<DEAD_UI> ui) {
  this->uis.push_back(ui);
}
std::vector<std::shared_ptr<DEAD_UI>> DEAD_UIDirector::getUis() {
  return this->uis;
}
