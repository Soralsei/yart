#include "yart/core/world.h"

#include "yart/core/material.h"
#include "yart/core/ray.h"
#include "yart/geometry/sphere.h"
#include "yart/geometry/transform.h"
#include "yart/light/light.h"
#include "yart/light/point_light.h"

namespace yart {

  World::World() {
    // LightPtr default_light = std::make_shared<light::PointLight>(Eigen::Vector3f{-10, 10, -10});
    // lights.push_back(default_light);

    // Material mat = Material{};
    // mat.set_diffuse_color(color::Color{0.8, 1.0, 0.6}).set_diffuse(0.7).set_specular(0.2);

    // auto sphere1 = std::make_shared<geometry::Sphere>();
    // sphere1->set_material(mat);
    // objects.push_back(sphere1);

    // geometry::Transform3D transform
    //     = geometry::Transform3D::Identity() * transform::scaling<float>(0.5, 0.5, 0.5);
    // auto sphere2 = std::make_shared<geometry::Sphere>(transform, 1.0);
    // objects.push_back(sphere2);
  }

  std::unique_ptr<World> World::default_world() {
    World *world = new World();

    LightPtr default_light = std::make_shared<light::PointLight>(Eigen::Vector3f{-10, 10, -10});
    world->lights.push_back(default_light);

    Material mat = Material{};
    mat.set_diffuse_color(color::Color{0.8f, 1.0f, 0.6f}).set_diffuse(0.7f).set_specular(0.2f);

    auto sphere1 = std::make_shared<geometry::Sphere>();
    sphere1->set_material(mat);
    world->objects.push_back(sphere1);

    geometry::Transform3D transform
        = geometry::Transform3D::Identity() * transform::scaling<float>(0.5f, 0.5f, 0.5f);
    auto sphere2 = std::make_shared<geometry::Sphere>(transform, 1.0f);
    world->objects.push_back(sphere2);

    return std::unique_ptr<World>(world);
  }

  Intersections World::intersections(const Ray &ray) {
    Intersections intersections;
    intersections.reserve(10000);

    for (auto &&object : objects) {
      Intersections i = object->intersections(ray);
      intersections.insert(std::end(intersections), std::begin(i), std::end(i));
    }
    auto key = [](const geometry::Intersection<Object3D> &a,
                  const geometry::Intersection<Object3D> &b) { return a.get_t() < b.get_t(); };
    std::sort(std::begin(intersections), std::end(intersections), key);
    return intersections;
  }

}  // namespace yart
