#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include <memory>

#include "yart/geometry/defines.hpp"
#include "yart/traits/comparable.hpp"

namespace yart {

  using namespace traits;

  class Ray;

  class Object3D : public std::enable_shared_from_this<Object3D>, public comparable_base<Object3D> {
  private:
    inline static uint32_t global_id = 0;

  protected:
    virtual bool is_equal(const Object3D& rhs) const override;
    virtual bool self_equal(const Object3D& other) const override;

    uint32_t object_id;

  public:
    Object3D(glm::vec3 _origin);
    Object3D(glm::vec3 _origin, glm::vec4 _rotation);
    Object3D(geometry::Transform _transform);
    Object3D();

    // Copy constructor
    Object3D(const Object3D& other) = default;
    Object3D(Object3D& other) = default;

    virtual ~Object3D();

    const glm::vec3& position() const;
    glm::vec3 orientation() const;
    const glm::quat& quaternion() const;

    friend std::ostream& operator<<(std::ostream& out, Object3D& shape);

    friend bool operator==(const Object3D& lhs, const Object3D& rhs);

    geometry::Transform transform;
  };

}  // namespace yart
