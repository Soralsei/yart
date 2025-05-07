#include <iostream>
#include <ostream>

#include "Eigen/Dense"
#include "yart/file/ppm_writer.h"
#include "yart/geometry/transform.h"
#include "yart/image/canvas.h"

using namespace yart;

struct Environment {
  Eigen::Vector3<float> gravity = {0, -9.81f, 0};
  Eigen::Vector3<float> wind = {0, 0, 0};
};

struct Projectile {
  Eigen::Vector3<float> position = {0, 0, 0};
  Eigen::Vector3<float> velocity = {10, 0, 5};
};

int main(int /*argc*/, char* /*argv*/[]) {
  Projectile p = {
      .position = {0, 1, 0},
      .velocity = Eigen::Vector3<float>{1, 1.8f, 0}.normalized() * 11.25f,
  };
  Environment e = {.gravity = {0, -0.1f, 0}, .wind{-0.01f, 0, 0}};

  image::Canvas<900, 550> canvas;
  image::Color trajectory_color{1.0, 192 / 255.0f, 203 / 255.0f};
  image::Color clock_color{1.0, 1.0, 1.0};

  file::PPMWriter writer;

  std::cout << "Environment: " << e.gravity << ", " << e.wind << std::endl;

  // Simulate the projectile motion
  for (int i = 0; i < 300; ++i) {
    if (canvas.getHeight() > p.position[1] && p.position[1] >= 0
        && p.position[0] < canvas.getWidth() && p.position[0] >= 0) {
      canvas.setPixel(p.position[0], canvas.getHeight() - p.position[1], trajectory_color);
    }
    p.position += p.velocity;
    p.velocity = p.velocity + e.wind + e.gravity;

    std::cout << "Position: " << p.position << ", Velocity: " << p.velocity << std::endl;
  }
  bool success = writer.write("/home/sora/trajectory.ppm", canvas.getPixels(), canvas.getWidth(),
                              canvas.getHeight());

  std::cout << "Final Position: " << p.position << ", Final Velocity: " << p.velocity << std::endl;

  return 0;
}