#include "yart/geometry/transform.h"

#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <Eigen/SVD>

namespace yart {
  namespace transform {

    Transform::Transform() {}

    Transform::Transform(const Eigen::Matrix4f& transform) {
      m_position = transform.col(3).head(3);
      Eigen::JacobiSVD<Eigen::Matrix3f> svd(transform.block(0, 0, 3, 3),
                                            Eigen::ComputeFullU | Eigen::ComputeFullV);

      float x = (svd.matrixU() * svd.matrixV().adjoint()).determinant() < 0 ? -1 : 1;
      Eigen::Vector3f sv(svd.singularValues());
      sv.coeffRef(2) *= x;
      Eigen::Matrix3f scale = svd.matrixV() * sv.asDiagonal() * svd.matrixV().adjoint();
      Eigen::Matrix3f m(svd.matrixU());
      m.col(2) *= x;
      m_orientation = Eigen::Quaternionf{m * svd.matrixV().adjoint()};
      m_scale = scale.diagonal();
    }

    Eigen::Matrix4f Transform::get_local_matrix() {
      Eigen::Matrix4f T = Eigen::Matrix4f::Identity();
      T.block(0, 3, 3, 1) = m_position;

      Eigen::Matrix4f R = Eigen::Matrix4f::Identity();
      R.block(0, 0, 3, 3) = m_orientation.toRotationMatrix();

      Eigen::Matrix4f S = Eigen::Matrix4f::Identity();
      S.block(0, 0, 3, 3) = m_scale.asDiagonal();

      m_local_matrix = T * R * S;
      return m_local_matrix;
    }

    void Transform::compute_model_matrix() {
      m_model_matrix = get_local_matrix();
      m_is_dirty = false;
    }

    void Transform::compute_model_matrix(const Eigen::Matrix4f& parent_matrix) {
      m_model_matrix = parent_matrix * get_local_matrix();
      m_is_dirty = false;
    }

    const Eigen::Matrix4f& Transform::matrix() const { return m_model_matrix; }

    bool Transform::is_dirty() const { return m_is_dirty; }

    const Eigen::Vector3f Transform::get_local_position() const { return m_position; }

    const Eigen::Quaternionf Transform::get_local_orientation() const { return m_orientation; }

    Transform& Transform::set_local_position(const Eigen::Vector3f& pos) {
      m_position = pos;
      m_is_dirty = true;
      return *this;
    }

    Transform& Transform::set_local_orientation(const Eigen::Quaternionf& orient) {
      m_orientation = orient;
      m_is_dirty = true;
      return *this;
    }

    Transform& Transform::rotate(const Eigen::Quaternionf& rot) {
      m_orientation *= rot;
      m_is_dirty = true;
      return *this;
    }

    Transform& Transform::rotate(const Eigen::Matrix3f& rot) {
      Eigen::Quaternionf R{rot};
      return rotate(R);
    }

    Transform& Transform::rotate(const Eigen::Matrix4f& rot) {
      Eigen::Quaternionf R{rot.block<3, 3>(Eigen::fix<0>, Eigen::fix<0>)};
      return rotate(R);
    }

    Transform& Transform::rotate(const Eigen::AngleAxisf& rot) {
      Eigen::Quaternionf R{rot};
      return rotate(R);
    }

    Transform& Transform::translate(const Eigen::Vector3f& translation) {
      m_position += translation;
      m_is_dirty = true;
      return *this;
    }

    Transform& Transform::translate(float x, float y, float z) {
      Eigen::Vector3f T{x, y, z};
      return translate(T);
    }

    Transform& Transform::rotate_x(float angle) {
      Eigen::AngleAxisf R(angle, Eigen::Vector3f::UnitX());
      return rotate(R);
    }

    Transform& Transform::rotate_y(float angle) {
      Eigen::AngleAxisf R(angle, Eigen::Vector3f::UnitY());
      return rotate(R);
    }

    Transform& Transform::rotate_z(float angle) {
      Eigen::AngleAxisf R(angle, Eigen::Vector3f::UnitZ());
      return rotate(R);
    }

    Transform operator*(const Transform& lhs, const Transform& rhs) {
      return Transform{lhs.m_model_matrix * rhs.m_model_matrix};
    }

  }  // namespace transform

}  // namespace yart
