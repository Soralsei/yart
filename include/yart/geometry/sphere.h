#pragma once
#include "yart/geometry/shape.h"

namespace yart {

  class Ray;

  namespace geometry {

    template <class ShapeType> class Intersection;  // forward declaration
    class Sphere : public Shape3D<Sphere> {
    private:
      float radius = 1.0f;

    public:
      Sphere(Transform3D transform, float _radius);
      Sphere(Eigen::Vector3f _origin, float _radius);
      Sphere(float _radius);
      Sphere();

      //Copy constructor
      Sphere(const Sphere& other);

      ~Sphere();

      std::vector<Intersection<Object3D>> intersections(const yart::Ray& ray);

      Eigen::Vector3f normal_at(const Eigen::Vector3f& point);

      friend std::ostream& operator<<(std::ostream& out, const Sphere& sphere);
    };

  }  // namespace geometry

}  // namespace yart
