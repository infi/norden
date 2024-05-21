#include "ButtonView.hpp"
#include "Gui.hpp"
#include "Logger.hpp"
#include "cairomm/context.h"
#include "cairomm/refptr.h"
#include "cairomm/surface.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <format>

constexpr int WIDTH = 400;
constexpr int HEIGHT = 400;

Cairo::RefPtr<Cairo::ImageSurface> create_surface(int width, int height) {
  return Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, width, height);
}

void resize(int width, int height) { glViewport(0, 0, width, height); }

int main() {
  glewInit();
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = SDL_CreateWindow(
      "Norden", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

  SDL_GLContext context = SDL_GL_CreateContext(window);
  SDL_GL_SetSwapInterval(1);
  SDL_GL_MakeCurrent(window, context);

  GLuint texture;
  glGenTextures(1, &texture);

  bool quit = false;
  SDL_Event event;

  int i = 0;

  ButtonView button =
      ButtonView(100, 100, 1000, 50, "Not clicked yet", [&button, &i]() {
        button.set_label(std::format("Clicked {} times", ++i));
      });
  auto gui = Gui(button);

  while (!quit) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = true;
      } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        gui.click(event.button);
      } else if (event.type == SDL_WINDOWEVENT) {
        if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
          resize(event.window.data1, event.window.data2);
        }
      }
    }

    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    auto surface = create_surface(w, h);

    auto cr = Cairo::Context::create(surface);
    cr->save();
    cr->set_source_rgb(0.0, 0.0, 0.0);
    cr->paint();

    gui.loop(cr);

    // draw to the surface
    cr->restore();

    // Make a gl texture from the surface
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 surface->get_data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Draw the texture
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(-1, 1);
    glTexCoord2f(1, 0);
    glVertex2f(1, 1);
    glTexCoord2f(1, 1);
    glVertex2f(1, -1);
    glTexCoord2f(0, 1);
    glVertex2f(-1, -1);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    SDL_GL_SwapWindow(window);

    // Clean up
    surface->finish();
  }

  // Clean up
  glDeleteTextures(1, &texture);

  return 0;
}
