#pragma once
#include <cmath>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/quaternion_float.hpp>

namespace yart {
  namespace transform {

    // clang-format off
    glm::mat4 shear(float xy, float xz, float yx, float yz, float zx, float zy);
    // clang-format on

    class Transform {
    protected:
      glm::vec3 m_position{0.0f, 0.0f, 0.0f};
      glm::quat m_orientation{1.0f, 0.0f, 0.0f, 0.0f};
      glm::vec3 m_scale{1.0f, 1.0f, 1.0f};

      glm::mat4 m_model_matrix{1.0f};
      glm::mat4 m_local_matrix{1.0f};

      bool m_is_dirty = false;
      bool m_is_local_dirty = false;

    protected:
      const glm::mat4& get_local_matrix();

    public:
      Transform();
      Transform(const glm::mat4& transform);

      void compute_model_matrix();
      void compute_model_matrix(glm::mat4 parent_matrix);

      glm::mat4 matrix();
      glm::mat4 matrix(glm::mat4 parent_matrix);
      bool is_dirty() const;

      const glm::vec3& get_local_position() const;
      const glm::quat& get_local_orientation() const;

      Transform& set_local_position(const glm::vec3& pos);
      Transform& set_local_orientation(const glm::quat& orient);
      Transform& set_local_scale(const glm::vec3& scale);

      Transform& rotate(glm::quat rot);
      Transform& rotate(glm::mat3 rot);
      Transform& rotate(glm::mat4 rot);
      Transform& rotate(float angle, float x, float y, float z);
      Transform& rotate(float angle, glm::vec3 axis);

      Transform& translate(glm::vec3 translation);
      Transform& translate(float x, float y, float z);
      Transform& scale(glm::vec3 _scale);
      Transform& scale(float x, float y, float z);

      Transform& rotate_x(float angle);
      Transform& rotate_y(float angle);
      Transform& rotate_z(float angle);

      friend Transform operator*(const Transform& lhs, const Transform& rhs);
    };

    Transform operator*(const Transform& lhs, const Transform& rhs);
  }  // namespace transform
}  // namespace yart
