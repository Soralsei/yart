#include "yart/core/ray.h"

#include <glm/gtx/io.hpp>
#include <iostream>

namespace yart {

  Ray::Ray(glm::vec3 _origin, glm::vec3 _direction) {
    origin = glm::vec4{_origin.x, _origin.y, _origin.z, 1.0f};
    direction = glm::vec4{_direction.x, _direction.y, _direction.z, 0.0f};
  }

  Ray::Ray(glm::vec4 _origin, glm::vec4 _direction) : origin(_origin), direction(_direction) {}

  Ray::Ray(glm::vec3 _direction) : Ray::Ray(glm::vec3{}, _direction) {}

  Ray::~Ray() {}

  glm::vec4 Ray::position(float t) const { return origin + direction * t; }
  const glm::vec4 Ray::get_direction() const { return direction; }
  const glm::vec4 Ray::get_origin() const { return origin; }

  Ray Ray::transform(geometry::Transform& T) const {
    auto mat = T.matrix();
    return transform(mat);
  }

  Ray Ray::transform(glm::mat4& transform) const {
    // std::cout << "Transform :\n" << transform << "\n";
    glm::vec4 origin_transformed = transform * origin;
    glm::vec4 direction_transformed = transform * direction;
    // std::cout << "Transformed Ray origin: " << origin_transformed << "\n";
    // std::cout << "Transformed Ray direction : " << direction_transformed << "\n";

    Ray transformed_ray{origin_transformed, direction_transformed};

    return transformed_ray;
  }

  std::ostream& operator<<(std::ostream& out, const Ray& ray) {
    out << "Ray(origin: [" << ray.get_origin() << "], direction: [" << ray.get_direction() << "])";
    return out;
  }
}  // namespace yart
