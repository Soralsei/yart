#include <iostream>
#include <ostream>

#include "Eigen/Dense"
#include "SDL3/SDL.h"
#include "yart/file/ppm_writer.h"
#include "yart/geometry/transform.h"
#include "yart/image/canvas.h"

using namespace yart;

int main(int /*argc*/, char* /*argv*/[]) {
  image::Canvas<900, 550> canvas;

  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  if (!SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return SDL_APP_FAILURE;
  }

  window = SDL_CreateWindow("Yart", 800, 600, SDL_WINDOW_VULKAN);
  if (!window) {
    std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return SDL_APP_FAILURE;
  }

  while (true)
  {
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