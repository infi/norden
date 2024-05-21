#pragma once

#include "cairomm/context.h"
#include "cairomm/refptr.h"
#include <optional>
#include <string>

class View {
public:
  View();
  virtual void render(Cairo::RefPtr<Cairo::Context> &ctx);
  virtual void click(int globalX, int globalY);
  virtual std::string stringify();

  int x;
  int y;
  int width;
  int height;

  // Check if the global coordinates are within the view's bounds
  bool is_within_bounds(int globalX, int globalY) {
    return globalX >= this->x && globalX <= this->x + this->width &&
           globalY >= this->y && globalY <= this->y + this->height;
  }

protected:
  // Map the global coordinates to local coordinates using the view's size and
  // position
  std::optional<std::tuple<int, int>> gloxy_as_locxy(int globalX, int globalY) {
    if (!is_within_bounds(globalX, globalY)) {
      return std::nullopt;
    }

    return std::optional<std::tuple<int, int>>{
        std::tuple<int, int>{globalX - this->x, globalY - this->y}};
  }
};