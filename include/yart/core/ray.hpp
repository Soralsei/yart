#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float4.hpp>
#include <iostream>

#include "yart/geometry/defines.hpp"

namespace yart {
  class Ray {
  private:
    glm::vec4 origin;
    glm::vec4 direction;

  public:
    Ray(glm::vec3 _origin, glm::vec3 _direction);
    Ray(glm::vec4 _origin, glm::vec4 _direction);
    Ray(glm::vec3 _direction);
    ~Ray();

    const glm::vec4 get_origin() const;
    const glm::vec4 get_direction() const;

    glm::vec4 position(float t) const;

    Ray transform(geometry::Transform& transform) const;
    Ray transform(glm::mat4& transform) const;

    friend std::ostream& operator<<(std::ostream& out, const Ray& ray);
  };
}  // namespace yart
