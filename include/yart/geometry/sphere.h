#pragma once
#include "shape.h"

namespace yart {

  class Ray;

  namespace geometry {

    template <class ShapeType> class Intersection;  // forward declaration
    class Sphere : public Shape<Sphere> {
    private:
      float radius = 1.0f;

    public:
      Sphere(Transform3d transform, float _radius);
      Sphere(Eigen::Vector3f _origin, float _radius);
      Sphere(float _radius);
      ~Sphere();

      std::vector<Intersection<Sphere>> intersections(const yart::Ray& ray);

      friend std::ostream& operator<<(std::ostream& out, const Sphere& sphere);
    };

  }  // namespace geometry

}  // namespace yart
