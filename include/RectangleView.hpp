#pragma once

#include "View.hpp"

class RectangleView : public View {
private:
  int color;

public:
  RectangleView(int x, int y, int width, int height, int color) : color(color) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
  }
  void render(Cairo::RefPtr<Cairo::Context> &ctx) override;
  void click(int globalX, int globalY) override;
  std::string stringify() override;
};
