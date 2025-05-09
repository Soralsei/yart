#include "yart/core/object3d.h"

#include <memory>

#include "yart/core/material.h"

namespace yart {

  Object3D::Object3D(Eigen::Vector3f _origin) {
    transform = geometry::Transform3D::Identity();
    transform = transform.translate(_origin);
    material = std::make_unique<Material>();
  }

  Object3D::Object3D(Eigen::Vector3f _origin, Eigen::Vector4f _rotation) {
    transform = geometry::Transform3D::Identity();
    auto rot = geometry::Quaternion{_rotation}.normalized().toRotationMatrix();
    transform = transform.rotate(rot).translate(_origin);
    material = std::make_unique<Material>();
  }

  Object3D::Object3D(geometry::Transform3D _transform) : transform(_transform) {
    material = std::make_unique<Material>();
  }
  Object3D::Object3D() : transform(geometry::Transform3D::Identity()) {
    material = std::make_unique<Material>();
  }

  std::vector<geometry::Intersection<Object3D>> Object3D::intersections(const yart::Ray&) {
    return std::vector<geometry::Intersection<Object3D>>{};
  }

  const geometry::Transform3D& Object3D::get_transform() const { return transform; }
  void Object3D::set_transform(const geometry::Transform3D& _transform) { transform = _transform; }

  Eigen::Vector3f Object3D::position() const { return transform.translation(); }
  Eigen::Vector3f Object3D::orientation() const {
    return transform.rotation().eulerAngles(2, 1, 0);
  }
  geometry::Quaternion Object3D::quaternion() const {
    return static_cast<geometry::Quaternion>(transform.rotation());
  }

  std::ostream& operator<<(std::ostream& out, const Object3D& shape) {
    return out << "Object3D(transform : " << shape.transform.matrix() << ")";
  }

  const Material& Object3D::get_material() const { return (*material); }

  Object3D& Object3D::set_material(const Material& _material) {
    (*material) = _material;
    return (*this);
  }

}  // namespace yart
