#include <iostream>
#include <ostream>

#include "Eigen/Dense"
#include "yart/file/ppm_writer.h"
#include "yart/geometry/transform.h"
#include "yart/image/canvas.h"

using namespace yart;

int main(int /*argc*/, char* /*argv*/[]) {
  image::Canvas canvas{900, 550};
  color::Color clock_color{1.0, 1.0, 1.0};

  file::PPMWriter writer;
  int radius = 100;  // pixels
  int offset_x = canvas.getWidth() / 2;
  int offset_y = canvas.getHeight() / 2;

  Eigen::Vector3f start = {0, 1, 0};

  for (size_t i = 0; i < 12; i++) {
    Eigen::Matrix3f rotation = yart::transform::rotationZ(static_cast<float>(-M_PI / 6 * i));
    auto rotated = rotation * (start * radius);
    canvas.setPixel(offset_x + rotated.x(), offset_y - rotated.y(), clock_color);
  }
  writer.write("/home/sora/clock.ppm", canvas.getPixels(), canvas.getWidth(), canvas.getHeight());

  return 0;
}