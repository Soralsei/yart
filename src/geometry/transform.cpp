#include "yart/geometry/transform.h"

#include <glm/gtx/io.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <iostream>

namespace yart {
  namespace transform {

    Transform::Transform() {}

    Transform::Transform(const glm::mat4& transform) {
      glm::vec3 skew;
      glm::vec4 perspective;
      glm::decompose(transform, m_scale, m_orientation, m_position, skew, perspective);
      m_local_matrix = transform;
      m_is_dirty = true;
    }

    const glm::mat4& Transform::get_local_matrix() {
      if (m_is_local_dirty) {
        std::cout << "Local matrix is dirty, recomputing local matrix.\n";
        glm::mat4 T = glm::translate(glm::mat4{1.0f}, m_position);
        glm::mat4 R = glm::mat4_cast(m_orientation);
        glm::mat4 S = glm::scale(glm::mat4{1.0f}, m_scale);
        m_local_matrix = T * R * S;
        m_is_local_dirty = false;
      }
      return m_local_matrix;
    }

    void Transform::compute_model_matrix() { compute_model_matrix(glm::mat4{1.0f}); }

    void Transform::compute_model_matrix(glm::mat4 parent_matrix) {
      auto local_matrix = get_local_matrix();
      m_model_matrix = parent_matrix * local_matrix;
      // Reset dirty flag after computing the model matrix
      std::cout << "Computed model matrix: " << m_model_matrix << "\n";
      m_is_dirty = false;
    }

    glm::mat4 Transform::matrix() { return matrix(glm::mat4{1.0f}); }
    glm::mat4 Transform::matrix(glm::mat4 parent_matrix) {
      if (m_is_dirty || m_is_local_dirty) {
        std::cout << "Transform is dirty, recomputing model matrix.\n";
        compute_model_matrix(parent_matrix);
      }
      return m_model_matrix;
    }

    bool Transform::is_dirty() const { return m_is_dirty; }

    const glm::vec3& Transform::get_local_position() const { return m_position; }
    const glm::quat& Transform::get_local_orientation() const { return m_orientation; }

    Transform& Transform::set_local_position(const glm::vec3& pos) {
      m_position = pos;
      m_is_local_dirty = true;
      return *this;
    }
    Transform& Transform::set_local_orientation(const glm::quat& orient) {
      m_orientation = orient;
      m_is_local_dirty = true;
      return *this;
    }
    Transform& Transform::set_local_scale(const glm::vec3& scale) {
      m_scale = scale;
      m_is_local_dirty = true;
      return *this;
    }

    Transform& Transform::rotate(glm::quat rot) { return rotate(glm::mat4_cast(rot)); }
    Transform& Transform::rotate(glm::mat3 rot) { return rotate(glm::mat4{rot}); }
    Transform& Transform::rotate(glm::mat4 rot) {
      m_orientation *= glm::quat_cast(rot);
      m_local_matrix = rot * m_local_matrix;
      m_is_dirty = true;
      return *this;
    }
    Transform& Transform::rotate(float angle, float x, float y, float z) {
      return rotate(angle, {x, y, z});
    }
    Transform& Transform::rotate(float angle, glm::vec3 axis) {
      m_orientation = glm::rotate(m_orientation, angle, axis);
      m_local_matrix = glm::rotate(m_local_matrix, angle, axis);
      m_is_dirty = true;
      return *this;
    }

    Transform& Transform::translate(glm::vec3 translation) {
      m_position += translation;
      m_local_matrix = glm::translate(m_local_matrix, translation);
      m_is_dirty = true;
      return *this;
    }
    Transform& Transform::translate(float x, float y, float z) {
      return translate(glm::vec3{x, y, z});
    }

    Transform& Transform::scale(glm::vec3 _scale) {
      m_scale *= _scale;
      m_local_matrix = glm::scale(m_local_matrix, _scale);
      m_is_dirty = true;
      return *this;
    }
    Transform& Transform::scale(float x, float y, float z) { return scale(glm::vec3{x, y, z}); }

    Transform& Transform::rotate_x(float angle) { return rotate(angle, {1, 0, 0}); }
    Transform& Transform::rotate_y(float angle) { return rotate(angle, {0, 1, 0}); }
    Transform& Transform::rotate_z(float angle) { return rotate(angle, {0, 0, 1}); }

    Transform operator*(const Transform& lhs, const Transform& rhs) {
      return Transform{lhs.m_model_matrix * rhs.m_model_matrix};
    }

    // clang-format off
    glm::mat4 shear(float xy, float xz, float yx, float yz, float zx, float zy) {
      return glm::mat4{
        1, yx, zx, 0,
        xy, 1, zy, 0,
        xz, yz, 1, 0,
        0, 0, 0, 1,
      };
    }
    // clang-format on

  }  // namespace transform

}  // namespace yart
