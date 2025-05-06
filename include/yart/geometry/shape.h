#pragma once
#include <memory>

#include "Eigen/Dense"
#include "yart/traits/named_type.h"

namespace yart {

  class Ray;
  class Intersection;

  namespace geometry {

    template <class Derived> class Shape : public std::enable_shared_from_this<Derived> {
    protected:
      Eigen::Vector4f origin;

    public:
      Shape(Eigen::Vector4f _origin) : origin(_origin) {}
      ~Shape() {}

      Derived& derived() { return static_cast<Derived>((*this)); }

      std::vector<Intersection<Derived>> intersections(const yart::Ray& ray) {
        return derived().intersections(ray);
      }

      friend bool operator==(const Derived& lhs, const Derived& rhs) { return lhs.equals(rhs); }

      friend std::ostream& operator<<(std::ostream& out, const Shape<Derived>& shape) {
        return out << shape.derived();
      }
    };

  }  // namespace geometry

}  // namespace yart
