#pragma once
#include "Eigen/Dense"
#include "yart/core/object3d.h"
#include "yart/geometry/defines.h"

namespace yart {

  class Ray;

  namespace geometry {
    template <class ShapeType> class Intersection;
    template <class Derived> class Shape3D : public Object3D<Derived> {
    public:
      Shape3D(Eigen::Vector3f _origin) : Object3D<Derived>::Object3D(_origin) {}

      Shape3D(Eigen::Vector3f _origin, Eigen::Vector4f _rotation) : Object3D<Derived>::Object3D(_origin, _rotation) {}

      Shape3D(Transform3d _transform) : Object3D<Derived>::Object3D(_transform) {}
      Shape3D() : Object3D<Derived>::Object3D() {}
      ~Shape3D() {}

      inline Derived& derived() { return *static_cast<Derived*>(this); }
      inline const Derived& derived() const { return *static_cast<Derived*>(this); }

      std::vector<Intersection<Derived>> intersections(const yart::Ray& ray) {
        return derived().intersections(ray);
      }

      Eigen::Vector3f normal_at(const Eigen::Vector3f& point) { return derived().normal_at(point); }
    };

  }  // namespace geometry

}  // namespace yart
