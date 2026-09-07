#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtx/io.hpp>
#include <iostream>
#include <memory>
#include <ostream>

#include "yart/core/camera.hpp"
#include "yart/core/material.hpp"
#include "yart/core/world.hpp"
#include "yart/file/png_writer.hpp"
#include "yart/file/ppm_writer.hpp"
#include "yart/geometry/primitives/sphere.hpp"
#include "yart/geometry/transform.hpp"
#include "yart/image/canvas.hpp"
#include "yart/image/color_format.hpp"
#include "yart/light/point_light.hpp"

using namespace yart;

int main(int /*argc*/, char* /*argv*/[]) {
  Camera camera{640, 480, M_PI / 3};
  // Camera camera{480, 360, M_PI / 2};
  camera.transform
      = Camera::get_view_transform(glm::vec3{0, 1.0, -5}, glm::vec3{0, 1, 0}, glm::vec3{0, 1, 0});

  std::cout << "Camera view matrix :\n" << camera.transform.matrix() << '\n';

#ifdef YART_USE_LIBPNG
  file::PNGWriter<image::RGB888Format> writer;
#  define FILENAME "/home/sora/world_render.png"
#else
  file::PPMWriter writer;
#  define FILENAME "/home/sora/world_render.ppm"
#endif

  auto flat_scale = glm::vec3{10, 0.01, 10};
  auto material = std::make_shared<Material>();
  material->set_diffuse_color(color::Color{1, 0.9f, 0.9f}).set_specular(0);

  ObjectPtr floor = std::make_shared<geometry::Sphere>();
  floor->set_material(material);
  floor->transform.scale(flat_scale);

  ObjectPtr left_wall = std::make_shared<geometry::Sphere>();
  left_wall->set_material(material);
  left_wall->transform.translate(0, 0, 5).rotate_y(-M_PI_4).rotate_x(M_PI_2).scale(flat_scale);

  ObjectPtr right_wall = std::make_shared<geometry::Sphere>();
  right_wall->set_material(material);
  right_wall->transform.translate(0, 0, 5).rotate_y(M_PI_4).rotate_x(M_PI_2).scale(flat_scale);

  ObjectPtr middle = std::make_shared<geometry::Sphere>();
  middle->transform.translate(-0.5, 1, 0.5);
  middle->get_material()
      .set_diffuse_color(color::Color{0.1, 1, 0.5})
      .set_diffuse(0.7)
      .set_specular(0.3);

  ObjectPtr right = std::make_shared<geometry::Sphere>();
  right->transform.translate(1.0, 0.5, -0.5).scale(glm::vec3{0.5, 0.5, 0.5});
  right->get_material()
      .set_diffuse_color(color::Color{0.5, 1, 0.1})
      .set_diffuse(0.7)
      .set_specular(0.3);

  ObjectPtr left = std::make_shared<geometry::Sphere>();
  left->transform.translate(-1.0, 0.33, -0.75).scale(glm::vec3{0.33, 0.33, 0.33});
  left->get_material()
      .set_diffuse_color(color::Color{1, 0.8, 0.1})
      .set_diffuse(0.7)
      .set_specular(0.3);

  LightPtr light = std::make_shared<light::PointLight>(glm::vec3{-10, 10, -10});
  // World world = *World::default_world();
  World world;
  world.add_object(floor)
      .add_object(left_wall)
      .add_object(right_wall)
      .add_object(middle)
      .add_object(right)
      .add_object(left)
      .add_light(light);

  std::cout << "World object :\n";
  for (auto&& obj : world.get_objects()) {
    std::cout << "- " << (*obj) << '\n';
  }
  std::cout << "\nWorld light sources :\n";
  for (auto&& obj : world.get_light_sources()) {
    std::cout << "- " << (*obj) << '\n';
  }

  auto image = world.render(camera);

  writer.write(FILENAME, image->getPixels(), image->getWidth(), image->getHeight());

  return 0;
}