#pragma once

#include "CompositeView.hpp"
#include "RectangleView.hpp"
#include "TextView.hpp"
#include <functional>
#include <vector>

class ButtonView : public CompositeView {
private:
  std::string label;
  std::function<void()> onClick;

public:
  ButtonView(int x, int y, int width, int height, std::string label,
             std::function<void()> onClick)
      : CompositeView(x, y, {}), label(label), onClick(onClick) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    auto rectView =
        std::make_shared<RectangleView>(x, y, width, height, 0x212121);
    auto textView =
        std::make_shared<TextView>(x + 10, y + 13, width, height, label);
    this->add(rectView);
    this->add(textView);
  }
  void click(int globalX, int globalY) override;
  std::string stringify() override;

  ~ButtonView() { this->clear(); }
};