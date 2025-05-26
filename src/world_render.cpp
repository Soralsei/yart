#include <iostream>
#include <memory>
#include <ostream>

#include "Eigen/Dense"
#include "yart/core/camera.h"
#include "yart/core/material.h"
#include "yart/core/ray.h"
#include "yart/core/world.h"
#include "yart/file/ppm_writer.h"
#include "yart/geometry/intersection.h"
#include "yart/geometry/sphere.h"
#include "yart/geometry/transform.h"
#include "yart/image/canvas.h"
#include "yart/light/point_light.h"

using namespace yart;

int main(int /*argc*/, char* /*argv*/[]) {
  Camera camera{640, 480, M_PI / 3};
  // Camera camera{480, 360, M_PI / 2};
  camera.transform = Camera::get_view_transform(Eigen::Vector3f{0, 1.0, -5},
                                                Eigen::Vector3f::UnitY(), Eigen::Vector3f::UnitY());

  std::cout << "Camera view matrix :\n" << camera.transform.matrix() << '\n';

  file::PPMWriter writer;

  auto flat_scale = transform::scale<float>(10, 0.01, 10);
  auto material = std::make_shared<Material>();
  material->set_diffuse_color(color::Color{1, 0.9, 0.9}).set_specular(0);

  ObjectPtr floor = std::make_shared<geometry::Sphere>();
  floor->set_material(material);
  floor->transform.scale(flat_scale.diagonal());

  ObjectPtr left_wall = std::make_shared<geometry::Sphere>();
  left_wall->set_material(material);
  left_wall->transform.translate(transform::translation<float>(0, 0, 5).translation())
      .rotate(transform::rotationY<float>(-M_PI_4))
      .rotate(transform::rotationX<float>(M_PI_2))
      .scale(flat_scale.diagonal());

  ObjectPtr right_wall = std::make_shared<geometry::Sphere>();
  right_wall->set_material(material);
  right_wall->transform.translate(transform::translation<float>(0, 0, 5).translation())
      .rotate(transform::rotationY<float>(M_PI_4))
      .rotate(transform::rotationX<float>(M_PI_2))
      .scale(flat_scale.diagonal());

  ObjectPtr middle = std::make_shared<geometry::Sphere>();
  middle->transform.translate(transform::translation<float>(-0.5, 1, 0.5).translation());
  middle->get_material()
      .set_diffuse_color(color::Color{0.1, 1, 0.5})
      .set_diffuse(0.7)
      .set_specular(0.3);

  ObjectPtr right = std::make_shared<geometry::Sphere>();
  right->transform.translate(transform::translation<float>(1.0, 0.5, -0.5).translation())
      .scale(Eigen::Vector3f{0.5, 0.5, 0.5});
  right->get_material()
      .set_diffuse_color(color::Color{0.5, 1, 0.1})
      .set_diffuse(0.7)
      .set_specular(0.3);

  ObjectPtr left = std::make_shared<geometry::Sphere>();
  left->transform.translate(transform::translation<float>(-1.0, 0.33, -0.75).translation())
      .scale(Eigen::Vector3f{0.33, 0.33, 0.33});
  left->get_material()
      .set_diffuse_color(color::Color{1, 0.8, 0.1})
      .set_diffuse(0.7)
      .set_specular(0.3);

  LightPtr light = std::make_shared<light::PointLight>(Eigen::Vector3f{-10, 10, -10});
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

  writer.write("/home/sora/world_render.ppm", image->getPixels(), image->getWidth(),
               image->getHeight());

  return 0;
}