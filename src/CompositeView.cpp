#include "CompositeView.hpp"
#include "Logger.hpp"
#include <format>

void CompositeView::render(Cairo::RefPtr<Cairo::Context> &ctx) {
  for (auto &child : children) {
    child->render(ctx);
  }
}

void CompositeView::click(int globalX, int globalY) {
  for (auto &child : children) {
    Logger::log(
        std::format("Checking if {} is within bounds of ({}, {}) to ({}, {})",
                    child->stringify(), x, y, x + width, y + height));
    if (child->is_within_bounds(globalX, globalY)) {
      Logger::log(std::format("Clicking on {} at ({}, {})", child->stringify(),
                              globalX, globalY));
      child->click(globalX - x, globalY - y);
    }
  }
}

void CompositeView::add(std::shared_ptr<View> view) {
  children.push_back(view);
}

void CompositeView::remove(std::shared_ptr<View> view) {
  children.erase(std::remove(children.begin(), children.end(), view),
                 children.end());
}

void CompositeView::clear() { children.clear(); }

std::string CompositeView::stringify() {
  std::string result = "CompositeView(";
  for (auto &child : children) {
    result += child->stringify() + ", ";
  }
  result += ")";
  return result;
}
