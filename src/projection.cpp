#include <iostream>
#include <memory>
#include <ostream>

#include "Eigen/Dense"
#include "yart/core/ray.h"
#include "yart/file/ppm_writer.h"
#include "yart/geometry/intersection.h"
#include "yart/geometry/sphere.h"
#include "yart/geometry/transform.h"
#include "yart/image/canvas.h"

using namespace yart;

int main(int /*argc*/, char* /*argv*/[]) {
  image::Canvas<100, 100> canvas;
  color::Color hit_color{1.0, 0, 0};

  file::PPMWriter writer;

  float canvas_world_width = 7.0f;
  float canvas_world_height = 7.0f;

  auto sphere = std::make_shared<geometry::Sphere>(1.0f);

  auto transform = geometry::Transform3D{transform::shear<float>(1, 0, 0, 0, 0, 0)};
  sphere->set_transform(transform);

  double half_width = canvas_world_width / 2;
  double half_height = canvas_world_height / 2;
  double x_pixel_size = canvas_world_width / canvas.getWidth();
  double y_pixel_size = canvas_world_height / canvas.getHeight();

  for (size_t y = 0; y < canvas.getHeight(); y++) {
    float world_y = half_height - y * y_pixel_size;
    for (size_t x = 0; x < canvas.getWidth(); x++) {
      float world_x = -half_width + x_pixel_size * x;
      auto ray_origin = Eigen::Vector3f{0, 0, -5};
      auto ray_direction = (Eigen::Vector3f{world_x, world_y, 10} - ray_origin).normalized();
      Ray r{ray_origin, ray_direction};
      auto intersections = sphere->intersections(r);
      auto hit = geometry::hit(intersections);
      if (hit == nullptr) {
        canvas.setPixel(x, canvas.getHeight() - 1 - y, color::Black);
        continue;
      }

      canvas.setPixel(x, canvas.getHeight() - 1 - y, hit_color);
      std::cout << "Hit: " << (*hit) << "\n";
    }
  }

  writer.write("/home/sora/projection.ppm", canvas.getPixels(), canvas.getWidth(),
               canvas.getHeight());

  return 0;
}