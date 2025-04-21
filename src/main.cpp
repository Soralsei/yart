#include <iostream>
#include <ostream>

#include "Eigen/Dense"

#include "SDL3/SDL.h"
#include "yart/file/ppm_writer.h"
#include "yart/image/canvas.h"
#include "yart/math/transform.h"

using namespace yart;

// struct Environment {
//   Eigen::Vector3<float> gravity = {0, -9.81f, 0};
//   Eigen::Vector3<float> wind = {0, 0, 0};
// };

// struct Projectile {
//   Eigen::Vector3<float> position = {0, 0, 0};
//   Eigen::Vector3<float> velocity = {10, 0, 5};
// };

int main(int /*argc*/, char* /*argv*/[]) {
  // Projectile p = {
  //     .position = {0, 1, 0},
  //     .velocity = Eigen::Vector3<float>{1, 1.8f, 0}.normalized() * 11.25f,
  // };
  // Environment e = {.gravity = {0, -0.1f, 0}, .wind{-0.01f, 0, 0}};

  image::Canvas<900, 550> canvas;
  // image::Color trajectory_color{1.0, 192 / 255.0f, 203 / 255.0f};
  image::Color clock_color{1.0, 1.0, 1.0};

  file::PPMWriter writer;

  // SDL_Window *window = nullptr;
  // SDL_Renderer *renderer = nullptr;
  // if (!SDL_Init(SDL_INIT_VIDEO) != 0) {
  //   std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
  //   return SDL_APP_FAILURE;
  // }

  // window = SDL_CreateWindow("Projectile Motion", 800, 600, SDL_WINDOW_VULKAN);
  // if (!window) {
  //   std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
  //   SDL_Quit();
  //   return SDL_APP_FAILURE;
  // }

  // while (true)
  // {
  //   SDL_Event event;
  //   while (SDL_PollEvent(&event)) {
  //     if (event.type == SDL_EVENT_QUIT) {
  //       SDL_DestroyWindow(window);
  //       SDL_Quit();
  //       return 0;
  //     }
  //   }

  //   // Clear the window
  //   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  //   SDL_RenderClear(renderer);

  //   // Draw the projectile
  //   SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  //   SDL_RenderPoint(renderer, p.position[0], p.position[1]);

  //   // Present the renderer
  //   SDL_RenderPresent(renderer);
  // }

  // std::cout << "Environment: " << e.gravity << ", " << e.wind << std::endl;

  // Simulate the projectile motion
  // for (int i = 0; i < 300; ++i) {
  //   if (canvas.getHeight() > p.position[1] && p.position[1] >= 0
  //       && p.position[0] < canvas.getWidth() && p.position[0] >= 0) {
  //     canvas.setPixel(p.position[0], canvas.getHeight() - p.position[1], trajectory_color);
  //   }
  //   p.position += p.velocity;
  //   p.velocity = p.velocity + e.wind + e.gravity;

  //   std::cout << "Position: " << p.position << ", Velocity: " << p.velocity << std::endl;
  // }

  // bool success = writer.write("/home/sora/trajectory.ppm", canvas.getPixels(), canvas.getWidth(),
  //                             canvas.getHeight());

  // std::cout << "Final Position: " << p.position << ", Final Velocity: " << p.velocity << std::endl;

  // SDL_Log("Final Position: %f, %f, %f", p.position[0], p.position[1], p.position[2]);

  int radius = 100; // pixels
  int offset_x = canvas.getWidth() / 2;
  int offset_y = canvas.getHeight() / 2;
  Eigen::Vector4f start = {0, 1, 0, 1};
  for (size_t i = 0; i < 12; i++)
  {
    Eigen::Matrix4f rotation = yart::transform::rotationZ(static_cast<float>(-M_PI / 6 * i));
    auto rotated = rotation * (start * radius);
    canvas.setPixel(offset_x + rotated.x(), offset_y - rotated.y(), clock_color);
  }
  writer.write("/home/sora/clock.ppm", canvas.getPixels(), canvas.getWidth(), canvas.getHeight());
  

  return 0;
}