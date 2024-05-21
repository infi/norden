#include "RectangleView.hpp"
#include <format>

void RectangleView::render(Cairo::RefPtr<Cairo::Context> &cr) {
  cr->set_source_rgb(((this->color >> 16) & 0xFF) / 255.0,
                     ((this->color >> 8) & 0xFF) / 255.0,
                     (this->color & 0xFF) / 255.0);

  cr->rectangle(this->x, this->y, this->width, this->height);
  cr->fill();
}
void RectangleView::click(int, int) {}
std::string RectangleView::stringify() {
  return std::format("RectangleView(colour: {})", this->color);
}
