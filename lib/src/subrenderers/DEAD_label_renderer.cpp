#include <memory>
#include <subrenderers/DEAD_subrenderer_base.h>
#include <subrenderers/DEAD_label_renderer.h>
#include <labels/DEAD_label_base.h>
#include <labels/DEAD_point_label.h>

DEAD_LabelRenderer::DEAD_LabelRenderer(DEAD_Renderer* renderer) :
  DEAD_SubRendererBase(renderer) {
}

void DEAD_LabelRenderer::addLabel(std::unique_ptr<DEAD_LabelBase>& label) {
  this->labels.push_back(std::move(label));
}

DEAD_LabelRenderer::~DEAD_LabelRenderer() {}

void DEAD_LabelRenderer::render() {
  for (const std::unique_ptr<DEAD_LabelBase>& label : this->labels) {
    label->render();
  }
  this->labels.clear();
}
