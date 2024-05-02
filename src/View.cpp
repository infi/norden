#include "View.hpp"

View::View() {}
void View::render(Cairo::RefPtr<Cairo::Context> &) {}
void View::click(int, int) {}
std::string View::stringify() { return "View"; }