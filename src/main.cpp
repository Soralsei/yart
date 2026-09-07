#include <SDL3/SDL.h>

#include <argparsepp/argparse.hpp>
#include <cstdint>
#include <iostream>
#include <ostream>

#include "yart/file/ppm_writer.hpp"
#include "yart/geometry/transform.hpp"
#include "yart/image/canvas.hpp"

using namespace yart;

int main(int argc, char *argv[]) {
  argparse::ArgumentParser parser;
  parser.add_argument("--seed", "-s")
      .default_value(0)
      .type<int>()
      .help("Random number generator seed");
  // Flags
  parser.add_argument("--disable-pixel-jitter").store_true().help("Disable pixel jitter");
  parser.add_argument("--disable-wavelength-jitter").store_true().help("Disable wavelength jitter");
  parser.add_argument("--disable-texture-filtering").store_true().help("Disable texture filtering");
  parser.add_argument("--force-diffuse").store_true().help("Force diffuse");
  parser.add_argument("--gpu", "-g").store_true().help("Use the GPU for rendering");

  parser.add_argument("--width", "-w")
      .type<uint32_t>()
      .default_value(900)
      .help("Width of the viewport (in px.)");
  parser.add_argument("--height")
      .type<uint32_t>()
      .default_value(550)
      .help("Height of the viewport (in px.)");

  parser.parse_args(argc, argv);

  uint32_t width = parser.get<uint32_t>("width");
  uint32_t height = parser.get<uint32_t>("height");

  image::Canvas canvas{width, height};

  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  if (!SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return SDL_APP_FAILURE;
  }

  window = SDL_CreateWindow("Yart", static_cast<int>(width), static_cast<int>(height),
                            SDL_WINDOW_VULKAN);
  if (!window) {
    std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return SDL_APP_FAILURE;
  }

  while (true) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
      }
    }

    // Clear the window
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Present the renderer
    SDL_RenderPresent(renderer);
  }

  return 0;
}