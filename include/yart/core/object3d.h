#pragma once
#include <memory>

#include "Eigen/Dense"
#include "yart/geometry/defines.h"

namespace yart {

  class Ray;

  template <class ShapeType> class Intersection;

  template <class Derived> class Object3D : public std::enable_shared_from_this<Derived> {
  protected:
    geometry::Transform3D transform;

  public:
    Object3D(Eigen::Vector3f _origin) {
      transform = geometry::Transform3D::Identity();
      transform = transform.translate(_origin);
    }

    Object3D(Eigen::Vector3f _origin, Eigen::Vector4f _rotation) {
      transform = geometry::Transform3D::Identity();
      transform = transform.rotate(_rotation).translate(_origin);
    }

    Object3D(geometry::Transform3D _transform) : transform(_transform) {}
    Object3D() : transform(geometry::Transform3D::Identity()) {}
    ~Object3D() {}

    inline Derived& derived() { return *static_cast<Derived*>(this); }
    inline const Derived& derived() const { return *static_cast<Derived*>(this); }

    std::vector<Intersection<Derived>> intersections(const yart::Ray& ray) {
      return derived().intersections(ray);
    }

    Eigen::Vector3f normal_at(const Eigen::Vector3f& point) { return derived().normal_at(point); }

    inline const geometry::Transform3D& get_transform() const { return transform; }
    inline void set_transform(const geometry::Transform3D& _transform) { transform = _transform; }
    // inline void set_transform(const Eigen::Matrix4f& _transform) { transform = _transform; }

    inline Eigen::Vector3f position() const { return transform.translation(); }
    // Returns euler angles in the order Yaw, Pitch, Roll
    inline Eigen::Vector3f orientation() const { return transform.rotation().eulerAngles(2, 1, 0); }
    inline geometry::Quaternion quaternion() const {
      return static_cast<geometry::Quaternion>(transform.rotation());
    }

    friend bool operator==(const Derived& lhs, const Derived& rhs) { return lhs.equals(rhs); }

    friend std::ostream& operator<<(std::ostream& out, const Object3D<Derived>& shape) {
      return out << shape.derived();
    }
  };

}  // namespace yart
