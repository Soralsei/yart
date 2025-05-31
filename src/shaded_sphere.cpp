#include <glm/geometric.hpp>
#include <memory>

#include "yart/core/material.hpp"
#include "yart/core/ray.hpp"
#include "yart/file/ppm_writer.hpp"
#include "yart/geometry/intersection.hpp"
#include "yart/geometry/primitives/sphere.hpp"
#include "yart/image/canvas.hpp"
#include "yart/light/point_light.hpp"

using namespace yart;

int main(int /*argc*/, char* /*argv*/[]) {
  image::Canvas canvas{50, 50};

  file::PPMWriter writer;

  float canvas_world_width = 7.0f;
  float canvas_world_height = 7.0f;

  Material material;
  material.set_diffuse_color(1, 0.2, 1);

  geometry::Transform transform = geometry::Transform{};
  // transform = transform * transform::shear<float>(1, 0, 0, 0, 0, 0);
  // transform = transform.translate(
  //     0, 0, 0) /** transform::rotationY<float>(M_PI_4) * transform::scale<float>(1, 0.5, 0.5)*/;

  // transform.rotate(Eigen::AngleAxisf(M_PI / 6, glm::vec3::UnitY()))
  // .rotate(Eigen::AngleAxisf(M_PI / 6, glm::vec3::UnitX()))
  // .;

  auto sphere = std::make_shared<geometry::Sphere>(transform, 1.0f);
  sphere->get_material() = material;

  auto light = light::PointLight{glm::vec3{-10, 10, -10}};

  // auto transform = geometry::Transform3D{transform::shear<float>(1, 0, 0, 0, 0, 0)};
  // sphere->transform = transform;

  double half_width = canvas_world_width / 2;
  double half_height = canvas_world_height / 2;
  double x_pixel_size = canvas_world_width / canvas.getWidth();
  double y_pixel_size = canvas_world_height / canvas.getHeight();

  for (size_t y = 0; y < canvas.getHeight(); y++) {
    float world_y = half_height - y * y_pixel_size;

    for (size_t x = 0; x < canvas.getWidth(); x++) {
      float world_x = -half_width + x_pixel_size * x;
      auto ray_origin = glm::vec3{0, 0, -5};
      auto ray_direction = glm::normalize(glm::vec3{world_x, world_y, 10} - ray_origin);

      Ray r{ray_origin, ray_direction};

      auto intersections = sphere->intersections(r);
      auto hit = geometry::hit(intersections);

      if (hit == nullptr) {
        canvas.setPixel(x, y, color::Black);
        continue;
      }

      glm::vec4 point = r.position(hit->get_t());
      glm::vec4 normal = sphere->normal_at(point);
      glm::vec4 eye = -r.get_direction();

      auto color = light::phong_lighting(sphere->get_material(), light, point, eye, normal);

      canvas.setPixel(x, y, color);
    }
  }

  writer.write("/home/sora/shaded.ppm", canvas.getPixels(), canvas.getWidth(), canvas.getHeight());

  return 0;
}