#include "cairomm/context.h"
#include <Gui.hpp>
#include <Logger.hpp>
#include <SDL2/SDL_timer.h>
#include <format>
#include <pangomm/init.h>

Gui::Gui(View &root) : root(root) {
  Pango::init();
  Logger::log(std::format("Gui(root: {})", root.stringify()));
}

void Gui::click(SDL_MouseButtonEvent event) {
  this->root.click(event.x, event.y);
}

void Gui::loop(Cairo::RefPtr<Cairo::Context> &cr) { this->root.render(cr); }