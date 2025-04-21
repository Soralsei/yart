#pragma once
#include "Eigen/Dense"

namespace yart {

  class Ray;

  namespace geometry {

    template <class Derived> class Shape {
    protected:
      Eigen::Vector4f origin;

    public:
      Shape(Eigen::Vector4f _origin) : origin(_origin) {}
      ~Shape() {}

      Derived& derived() { return static_cast<Derived>((*this)); }

      std::vector<float> intersections(const yart::Ray& ray) {
        return derived().intersections(ray);
      }

      friend bool operator==(const Derived& lhs, const Derived& rhs) {
        return lhs.equals(rhs);
      }
    };

  }  // namespace geometry

}  // namespace yart
