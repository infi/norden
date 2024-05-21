#include "GradientRectView.hpp"
#include "Logger.hpp"
#include <format>
#include <iostream>
#include <sys/types.h>

void GradientRectView::render(Cairo::RefPtr<Cairo::Context> &cr) {
  Cairo::RefPtr<Cairo::LinearGradient> gradient = Cairo::LinearGradient::create(
      this->x, this->y, this->x + this->width, this->y + this->height);

  for (ulong i = 0; i < this->stops.size(); i++) {
    int stop = this->stops[i];
    double offset = i / (this->stops.size() - 1.0);
    double r = ((stop >> 16) & 0xFF) / 255.0;
    double g = ((stop >> 8) & 0xFF) / 255.0;
    double b = (stop & 0xFF) / 255.0;

    gradient->add_color_stop_rgb(offset, r, g, b);
  }

  cr->set_source(gradient);
  cr->rectangle(this->x, this->y, this->width, this->height);
  cr->fill();
}

std::string GradientRectView::stringify() {
  std::string result = std::format("GradientRectView(stops: [");
  for (auto &stop : this->stops) {
    result += std::format("{:06X}", stop);
    if (&stop != &this->stops.back()) {
      result += ", ";
    }
  }
  result += "])";
  return result;
}