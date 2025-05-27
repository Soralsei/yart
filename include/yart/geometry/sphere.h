#pragma once
#include "yart/geometry/defines.h"
#include "yart/geometry/intersection.h"
#include "yart/geometry/shape.h"

namespace yart {

  namespace geometry {

    class Sphere : public comparable<Sphere, Object3D, Shape3D> {
      using Parent = comparable<Sphere, Object3D, Shape3D>;

    private:
      virtual std::vector<Intersection> local_intersections(const Ray& ray) override;
      virtual Eigen::Vector4f local_normal_at(const Eigen::Vector4f& point) const override;
      float radius = 1.0f;

    protected:
      virtual bool self_equal(const Sphere& other) const override;

    public:
      Sphere(Transform3D transform, float _radius);
      Sphere(Eigen::Vector3f _origin, float _radius);
      Sphere(float _radius);
      Sphere();

      // Copy constructor
      Sphere(const Sphere& other);

      ~Sphere();

      std::string as_string() const override;

      friend std::ostream& operator<<(std::ostream& out, const Sphere& sphere);
    };

  }  // namespace geometry

}  // namespace yart
