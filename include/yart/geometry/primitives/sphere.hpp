#pragma once
#include "yart/geometry/defines.hpp"
#include "yart/geometry/intersection.hpp"
#include "yart/geometry/shape.hpp"

namespace yart {

  namespace geometry {

    class Sphere : public comparable<Sphere, Object3D, Shape3D> {
      using Parent = comparable<Sphere, Object3D, Shape3D>;

    private:
      virtual std::vector<Intersection> local_intersections(const Ray& ray) override;
      virtual glm::vec4 local_normal_at(const glm::vec4& point) const override;
      float radius = 1.0f;

    protected:
      virtual bool self_equal(const Sphere& other) const override;

    public:
      Sphere(Transform transform, float _radius);
      Sphere(glm::vec3 _origin, float _radius);
      Sphere(float _radius);
      Sphere();

      // Copy constructor
      Sphere(const Sphere& other);

      ~Sphere();

      std::string as_string() override;

      friend std::ostream& operator<<(std::ostream& out, const Sphere& sphere);
    };

  }  // namespace geometry

}  // namespace yart
