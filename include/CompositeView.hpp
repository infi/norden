#pragma once

#include "View.hpp"
#include <memory>

class CompositeView : public View {
private:
  std::vector<std::shared_ptr<View>> children;

public:
  CompositeView(int x, int y, std::vector<std::shared_ptr<View>> children) {
    this->x = x;
    this->y = y;
    this->children = children;
  }
  void render(Cairo::RefPtr<Cairo::Context> &ctx) override;
  void click(int globalX, int globalY) override;
  void add(std::shared_ptr<View> view);
  void remove(std::shared_ptr<View> view);
  void clear();
  std::vector<std::shared_ptr<View>> get_children() { return children; }
  std::string stringify() override;

  ~CompositeView() { clear(); }
};