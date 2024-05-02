#pragma once

#include "View.hpp"
#include "cairomm/context.h"
#include <SDL2/SDL_events.h>

class Gui {
public:
  Gui(View &root);
  void click(SDL_MouseButtonEvent event);
  void loop(Cairo::RefPtr<Cairo::Context> &ctx);

private:
  View &root;
};