#include "RectangleView.hpp"
#include <format>
#include <random>

void RectangleView::render(Cairo::RefPtr<Cairo::Context> &cr) {
  cr->set_source_rgb(((this->color >> 16) & 0xFF) / 255.0,
                     ((this->color >> 8) & 0xFF) / 255.0,
                     (this->color & 0xFF) / 255.0);

  cr->rectangle(this->x, this->y, this->width, this->height);
  cr->fill();
}
void RectangleView::click(int globalX, int globalY) {
  auto localCoords = gloxy_as_locxy(globalX, globalY);

  if (!localCoords.has_value()) {
    return;
  }

  auto [localX, localY] = localCoords.value();

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 0xFFFFFF);

  this->color = dis(gen);
}
std::string RectangleView::stringify() {
  return std::format("RectangleView(colour: {})", this->color);
}
