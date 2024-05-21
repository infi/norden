#pragma once

#include "CompositeView.hpp"
#include "GradientRectView.hpp"
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

    std::vector<int> stops = {0x6743db, 0xa343db, 0xdb43bd};
    auto rectView =
        std::make_shared<GradientRectView>(x, y, width, height, stops);
    auto textView =
        std::make_shared<TextView>(x + 10, y + 13, width, height, label);
    this->add(rectView);
    this->add(textView);
  }
  void click(int globalX, int globalY) override;
  void render(Cairo::RefPtr<Cairo::Context> &ctx) override;
  std::string stringify() override;
  void set_label(std::string label) {
    this->label = label;
    auto textView = std::dynamic_pointer_cast<TextView>(get_children()[1]);
    textView->set_text(label);
  }

  ~ButtonView() { this->clear(); }
};