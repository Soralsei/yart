#include "yart/core/world.h"

#include "yart/core/camera.h"
#include "yart/core/material.h"
#include "yart/core/ray.h"
#include "yart/geometry/hit.h"
#include "yart/geometry/sphere.h"
#include "yart/geometry/transform.h"
#include "yart/image/canvas.h"
#include "yart/light/light.h"
#include "yart/light/point_light.h"

namespace yart {

  World::World() {}

  const std::vector<ObjectPtr> World::get_objects() const { return objects; }
  const std::vector<LightPtr> World::get_light_sources() const { return lights; }

  void World::add_object(ObjectPtr obj) { objects.push_back(obj); }
  void World::add_light(LightPtr light) { lights.push_back(light); }

  std::unique_ptr<World> World::default_world() {
    World *world = new World();

    LightPtr default_light = std::make_shared<light::PointLight>(Eigen::Vector3f{-10, 10, -10});
    world->lights.push_back(default_light);

    Material mat = Material{};
    mat.set_diffuse_color(color::Color{0.8f, 1.0f, 0.6f}).set_diffuse(0.7f).set_specular(0.2f);

    auto sphere1 = std::make_shared<geometry::Sphere>();
    sphere1->get_material() = mat;
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
    auto key = [](const geometry::Intersection &a, const geometry::Intersection &b) {
      return a.get_t() < b.get_t();
    };
    std::sort(std::begin(intersections), std::end(intersections), key);
    return intersections;
  }

  color::Color World::color_at(const Ray &ray) {
    auto intersects = intersections(ray);
    geometry::Intersection *h = geometry::hit(intersects);

    if (h == nullptr) {
      return color::Black;
    }

    auto hit = geometry::Hit::precompute_hit(ray, *h);
    return light::shade_hit(*this, *hit);
  }

  std::unique_ptr<image::Canvas> World::render(const Camera &camera) {
    uint32_t hsize = camera.get_hsize();
    uint32_t vsize = camera.get_vsize();

    std::unique_ptr<image::Canvas> image = std::make_unique<image::Canvas>(hsize, vsize);

    for (uint32_t y = 0; y < vsize; y++) {
      for (uint32_t x = 0; x < hsize; x++) {
        auto ray = camera.ray_to(x, y);
        auto color = color_at(ray);

        image->setPixel(x, y, color);
      }
    }
    return image;
  }

}  // namespace yart
