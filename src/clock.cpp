#include <glm/gtx/quaternion.hpp>

#include "yart/file/ppm_writer.h"
#include "yart/image/canvas.h"

using namespace yart;

int main(int /*argc*/, char* /*argv*/[]) {
  image::Canvas canvas{900, 550};
  color::Color clock_color{1.0, 1.0, 1.0};

  file::PPMWriter writer;
  int radius = 100;  // pixels
  int offset_x = canvas.getWidth() / 2;
  int offset_y = canvas.getHeight() / 2;

  glm::vec3 start = {0, 1, 0};

  for (size_t i = 0; i < 12; i++) {
    glm::mat4 rotation = glm::rotate(glm::identity<glm::mat4>(), static_cast<float>(-M_PI / 6 * i),
                                     glm::vec3{0, 0, 1});
    auto rotated = glm::mat3(rotation) * (start * static_cast<float>(radius));
    canvas.setPixel(offset_x + rotated.x, offset_y - rotated.y, clock_color);
  }
  writer.write("/home/sora/clock.ppm", canvas.getPixels(), canvas.getWidth(), canvas.getHeight());

  return 0;
}