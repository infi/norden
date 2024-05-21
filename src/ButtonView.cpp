#include "ButtonView.hpp"
#include "cairomm/types.h"
#include <format>

void ButtonView::click(int globalX, int globalY) {
  if (!is_within_bounds(globalX, globalY)) {
    return;
  }

  onClick();
}

void ButtonView::render(Cairo::RefPtr<Cairo::Context> &ctx) {
  // Set width to text width
  auto layout = Pango::Layout::create(ctx);
  layout->set_width(this->width * Pango::SCALE);
  layout->set_height(this->height * Pango::SCALE);
  auto font = Glib::ustring(std::format(
      "{} {} {}", TextConstants::DEFAULT_FONT_FAMILY,
      TextConstants::DEFAULT_FONT_WEIGHT, TextConstants::DEFAULT_FONT_SIZE));

  Pango::FontDescription desc(font);
  layout->set_font_description(desc);

  auto text = Glib::ustring(this->label);
  layout->set_text(text);

  int textWidth, textHeight;
  layout->get_pixel_size(textWidth, textHeight);

  this->width = textWidth + 20;
  this->height = textHeight + 20;

  for (auto &child : get_children()) {
    child->width = width;
    child->height = height;
  }

  CompositeView::render(ctx);
}

std::string ButtonView::stringify() {
  return std::format("ButtonView(label: {}, onClick: {})", label,
                     "[fx() -> void]");
}