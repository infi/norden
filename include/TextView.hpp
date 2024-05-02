#pragma once

#include "View.hpp"
#include "pangomm/layout.h"

class TextView : public View {
private:
  std::string text;
  Pango::Alignment alignment;

public:
  TextView(int x, int y, int width, int height, std::string text,
           Pango::Alignment alignment = Pango::Alignment::ALIGN_LEFT)
      : text(text) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->alignment = alignment;
  }
  void render(Cairo::RefPtr<Cairo::Context> &ctx) override;
  void click(int globalX, int globalY) override;
  std::string stringify() override;
};