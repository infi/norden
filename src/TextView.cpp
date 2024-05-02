#include "TextView.hpp"
#include <format>
#include <pangomm/layout.h>

void TextView::click(int, int) {}
void TextView::render(Cairo::RefPtr<Cairo::Context> &ctx) {
  ctx->set_source_rgb(1.0, 1.0, 1.0);
  ctx->move_to(x, y);

  auto layout = Pango::Layout::create(ctx);
  layout->set_width(this->width * Pango::SCALE);
  layout->set_height(this->height * Pango::SCALE);
  auto font = Glib::ustring("Inter Variable Bold 16");

  Pango::FontDescription desc(font);
  layout->set_font_description(desc);

  auto text = Glib::ustring(this->text);
  layout->set_text(text);

  layout->show_in_cairo_context(ctx);
}
std::string TextView::stringify() {
  return std::format("TextView(text: {})", text);
}