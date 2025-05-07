#pragma once
#include <memory>

#include "Eigen/Dense"
#include "yart/geometry/defines.h"
#include "yart/traits/named_type.h"

namespace yart {

  class Ray;

  namespace geometry {
    template <class ShapeType> class Intersection;

    template <class Derived> class Shape : public std::enable_shared_from_this<Derived> {
    public:
      Shape(Eigen::Vector3f _origin) {
        transform = Transform3d::Identity();
        transform = transform.translate(_origin);
      }

      Shape(Eigen::Vector3f _origin, Eigen::Vector4f _rotation) {
        transform = Transform3d::Identity();
        transform = transform.rotate(_rotation).translate(_origin);
      }

      Shape() : transform(Transform3d::Identity()) {}
      Shape(Transform3d _transform) : transform(_transform) {}
      ~Shape() {}

      Derived& derived() { return static_cast<Derived>((*this)); }

      std::vector<Intersection<Derived>> intersections(const yart::Ray& ray) {
        return derived().intersections(ray);
      }

      inline Eigen::Vector3f position() const { return transform.translation(); }
      // Returns euler angles in the order Yaw, Pitch, Roll
      inline Eigen::Vector3f orientation() const {
        return transform.rotation().eulerAngles(2, 1, 0);
      }
      inline Quaternion quaternion() const { return static_cast<Quaternion>(transform.rotation()); }

      friend bool operator==(const Derived& lhs, const Derived& rhs) { return lhs.equals(rhs); }

      friend std::ostream& operator<<(std::ostream& out, const Shape<Derived>& shape) {
        return out << shape.derived();
      }

      Transform3d transform;
    };

  }  // namespace geometry

}  // namespace yart
