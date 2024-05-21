#pragma once

#include "Const.hpp"
#include "View.hpp"
#include "pangomm/layout.h"

class TextView : public View {
private:
  std::string text;
  std::string fontFamily;
  std::string fontWeight;
  int fontSize;
  Pango::Alignment alignment;

public:
  TextView(int x, int y, int width, int height, std::string text,
           std::string fontFamily = TextConstants::DEFAULT_FONT_FAMILY,
           std::string fontWeight = TextConstants::DEFAULT_FONT_WEIGHT,
           int fontSize = TextConstants::DEFAULT_FONT_SIZE,
           Pango::Alignment alignment = Pango::Alignment::ALIGN_LEFT)
      : text(text) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->fontFamily = fontFamily;
    this->fontWeight = fontWeight;
    this->fontSize = fontSize;
    this->alignment = alignment;
  }
  void render(Cairo::RefPtr<Cairo::Context> &ctx) override;
  void click(int globalX, int globalY) override;
  std::string stringify() override;
};