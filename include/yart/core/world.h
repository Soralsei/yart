#pragma once
#include <memory>
#include <vector>

namespace yart {

  class Object3D;
  namespace geometry {
    template <class ObjectType> class Intersection;
  }  // namespace geometry

  class Ray;
  namespace light {
    class Light;
  }  // namespace light

  using ObjectPtr = std::shared_ptr<Object3D>;
  using LightPtr = std::shared_ptr<light::Light>;
  using Intersections = std::vector<geometry::Intersection<Object3D>>;

  class World {
  private:
    std::vector<ObjectPtr> objects;
    std::vector<LightPtr> lights;

  public:
    World();
    ~World() = default;

    Intersections intersections(const Ray& ray);

    static std::unique_ptr<World> default_world();
  };

}  // namespace yart
