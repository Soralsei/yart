#include "yart/core/object3d.h"

#include <memory>

#include "yart/core/material.h"
#include "yart/core/ray.h"

namespace yart {

  Object3D::Object3D(Eigen::Vector3f _origin) {
    transform = geometry::Transform3D::Identity();
    transform = transform.translate(_origin);

    object_id = global_id++;
  }

  Object3D::Object3D(Eigen::Vector3f _origin, Eigen::Vector4f _rotation) {
    transform = geometry::Transform3D::Identity();
    auto rot = geometry::Quaternion{_rotation}.normalized().toRotationMatrix();
    transform = transform.rotate(rot).translate(_origin);

    object_id = global_id++;
  }

  Object3D::Object3D(geometry::Transform3D _transform) : transform(_transform) {
    object_id = global_id++;
  }
  Object3D::Object3D() : transform(geometry::Transform3D::Identity()) { object_id = global_id++; }
  Object3D::~Object3D() {}
  
  // Object3D::Object3D(const Object3D& other)
  //     : transform(other.transform), object_id(other.object_id), material(other.material) {}

  const geometry::Transform3D& Object3D::get_transform() const { return transform; }
  void Object3D::set_transform(const geometry::Transform3D& _transform) { transform = _transform; }

  Eigen::Vector3f Object3D::position() const { return transform.translation(); }
  Eigen::Vector3f Object3D::orientation() const {
    return transform.rotation().eulerAngles(2, 1, 0);
  }
  geometry::Quaternion Object3D::quaternion() const {
    return static_cast<geometry::Quaternion>(transform.rotation());
  }

  std::ostream& operator<<(std::ostream& out, const Object3D& object) {
    return out << "Object3D(object_id: " << object.object_id
               << ", transform : " << object.transform.matrix() << ")";
  }

  bool Object3D::is_equal(const Object3D& other) const { return self_equal(other); }

  bool Object3D::self_equal(const Object3D& other) const {
    std::cout << "Self : " << (*this) << '\n';
    std::cout << "Other : " << other << '\n';
    return object_id == other.object_id && transform.isApprox(other.transform);
  }

  bool operator==(const Object3D& lhs, const Object3D& rhs) { return lhs.is_equal(rhs); }

}  // namespace yart
