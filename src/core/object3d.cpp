#include "yart/core/object3d.h"

#include <glm/ext/quaternion_float.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/io.hpp>

namespace yart {

  Object3D::Object3D(glm::vec3 _origin) {
    transform = geometry::Transform{};
    transform = transform.translate(_origin);

    object_id = global_id++;
  }

  Object3D::Object3D(glm::vec3 _origin, glm::vec4 _rotation) {
    transform = geometry::Transform{};
    auto rot = glm::quat{_rotation.w, _rotation.x, _rotation.y, _rotation.z};
    transform = transform.rotate(rot).translate(_origin);

    object_id = global_id++;
  }

  Object3D::Object3D(geometry::Transform _transform) : transform(_transform) {
    object_id = global_id++;
  }
  Object3D::Object3D() : transform(geometry::Transform{}) { object_id = global_id++; }
  Object3D::~Object3D() {}

  const glm::vec3& Object3D::position() const { return transform.get_local_position(); }
  glm::vec3 Object3D::orientation() const {
    return glm::eulerAngles(transform.get_local_orientation());
  }
  const glm::quat& Object3D::quaternion() const { return transform.get_local_orientation(); }

  std::ostream& operator<<(std::ostream& out, Object3D& object) {
    return out << "Object3D(object_id: " << object.object_id
               << ", transform : " << object.transform.matrix() << ")";
  }

  bool Object3D::is_equal(const Object3D& other) const { return self_equal(other); }

  bool Object3D::self_equal(const Object3D& other) const { return object_id == other.object_id; }

  bool operator==(const Object3D& lhs, const Object3D& rhs) { return lhs.is_equal(rhs); }

}  // namespace yart
