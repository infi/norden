#include "ButtonView.hpp"
#include <format>

void ButtonView::click(int globalX, int globalY) {
  if (!is_within_bounds(globalX, globalY)) {
    return;
  }

  onClick();
}

std::string ButtonView::stringify() {
  return std::format("ButtonView(label: {}, onClick: {})", label,
                     "[fx() -> void]");
}