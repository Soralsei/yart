#pragma once
#include <memory>
#include <vector>

#include "yart/image/color.h"

namespace yart {

  class Object3D;
  class Camera;
  namespace geometry {
    class Intersection;
    class Shape3D;
  }  // namespace geometry

  class Ray;
  namespace light {
    class Light;
  }  // namespace light

  namespace image {
    class Canvas;
  }  // namespace image

  using ObjectPtr = std::shared_ptr<geometry::Shape3D>;
  using LightPtr = std::shared_ptr<light::Light>;
  using Intersections = std::vector<geometry::Intersection>;

  class World {
  private:
    std::vector<ObjectPtr> objects;
    std::vector<LightPtr> lights;

  public:
    World();
    ~World() = default;

    const std::vector<ObjectPtr> get_objects() const;
    const std::vector<LightPtr> get_light_sources() const;

    void add_object(ObjectPtr object);
    void add_light(LightPtr light);

    Intersections intersections(const Ray& ray);

    color::Color color_at(const Ray& ray);
    std::unique_ptr<image::Canvas> render(const Camera& camera);

    static std::unique_ptr<World> default_world();
  };

}  // namespace yart
