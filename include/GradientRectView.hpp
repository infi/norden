#pragma once

#include "RectangleView.hpp"
#include <vector>

class GradientRectView : public RectangleView {
private:
  std::vector<int> stops;

public:
  GradientRectView(int x, int y, int width, int height, std::vector<int> stops)
      : RectangleView(x, y, width, height, 0xff00ff), stops(stops) {}

  void render(Cairo::RefPtr<Cairo::Context> &ctx) override;
  std::string stringify() override;
};