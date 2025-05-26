#pragma once
#include <cmath>

#include "Eigen/Dense"
#include "Eigen/Geometry"

namespace yart {
  namespace transform {

    template <typename T> auto translation(T x, T y, T z) {
      return Eigen::Translation<T, 3>{x, y, z};
      // Eigen::Matrix4<T> m;
      // m << 1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1;
      // return m;
    }

    template <typename T> Eigen::DiagonalMatrix<T, 3> scale(T x, T y, T z) {
      return Eigen::Scaling(x, y, z);
      // Eigen::Matrix4<T> m;
      // m << x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1;
      // return m;
    }

    template <typename T> Eigen::AngleAxis<T> rotationX(T theta) {
      return Eigen::AngleAxis{theta, Eigen::Vector3<T>::UnitX()};
      // Eigen::Matrix4<T> m;
      // m << 1, 0, 0, 0, 0, std::cos(theta), -std::sin(theta), 0, 0, std::sin(theta),
      // std::cos(theta),
      //     0, 0, 0, 0, 1;
      // return m;
    }

    template <typename T> Eigen::AngleAxis<T> rotationY(T theta) {
      return Eigen::AngleAxis{theta, Eigen::Vector3<T>::UnitY()};
      // Eigen::Matrix4<T> m;
      // m << std::cos(theta), 0, std::sin(theta), 0, 0, 1, 0, 0, -std::sin(theta), 0,
      // std::cos(theta),
      //     0, 0, 0, 0, 1;
      // return m;
    }

    template <typename T> Eigen::AngleAxis<T> rotationZ(T theta) {
      return Eigen::AngleAxis{theta, Eigen::Vector3<T>::UnitZ()};
      // Eigen::Matrix4<T> m;
      // m << std::cos(theta), -std::sin(theta), 0, 0, std::sin(theta), std::cos(theta), 0, 0, 0, 0,
      // 1,
      //     0, 0, 0, 0, 1;
      // return m;
    }

    template <typename T> Eigen::Matrix3<T> shear(T xy, T xz, T yx, T yz, T zx, T zy) {
      Eigen::Matrix3<T> m;
      m << 1, xy, xz, yx, 1, yz, zx, zy, 1;
      return m;
    }

    class Transform {
    protected:
      Eigen::Vector3f m_position = Eigen::Vector3f::Zero();
      Eigen::Quaternionf m_orientation = Eigen::Quaternionf::Identity();
      Eigen::Vector3f m_scale = Eigen::Vector3f::Ones();

      Eigen::Matrix4f m_model_matrix = Eigen::Matrix4f::Identity();
      Eigen::Matrix4f m_local_matrix = Eigen::Matrix4f::Identity();

      bool m_is_dirty = false;

    protected:
      Eigen::Matrix4f get_local_matrix();

    public:
      Transform();
      Transform(const Eigen::Matrix4f& transform);

      void compute_model_matrix();
      void compute_model_matrix(const Eigen::Matrix4f& parent_matrix);

      const Eigen::Matrix4f& matrix() const;
      bool is_dirty() const;

      const Eigen::Vector3f get_local_position() const;
      const Eigen::Quaternionf get_local_orientation() const;

      Transform& set_local_position(const Eigen::Vector3f& pos);
      Transform& set_local_orientation(const Eigen::Quaternionf& orient);

      Transform& rotate(const Eigen::Quaternionf& rot);
      Transform& rotate(const Eigen::Matrix3f& rot);
      Transform& rotate(const Eigen::Matrix4f& rot);
      Transform& rotate(const Eigen::AngleAxisf& rot);

      Transform& translate(const Eigen::Vector3f& translation);
      Transform& translate(float x, float y, float z);

      Transform& rotate_x(float angle);
      Transform& rotate_y(float angle);
      Transform& rotate_z(float angle);

      friend Transform operator*(const Transform& lhs, const Transform& rhs);
    };

    Transform operator*(const Transform& lhs, const Transform& rhs);

    // class Transform {
    // protected:
    //   Eigen::Vector3f m_position = Eigen::Vector3f::Zero();
    //   Eigen::Quaternionf m_orientation = Eigen::Quaternionf::Identity();
    //   Eigen::Vector3f m_scale = Eigen::Vector3f::Ones();

    //   Eigen::Matrix4f m_model_matrix = Eigen::Matrix4f::Identity();
    //   Eigen::Matrix4f m_local_matrix = Eigen::Matrix4f::Identity();

    //   bool m_is_dirty = false;

    // protected:
    //   Eigen::Matrix4f get_local_matrix() {
    //     Eigen::Matrix4f T = translation<float>(m_position.x(), m_position.y(), m_position.z());

    //     Eigen::Matrix4f R = Eigen::Matrix4f::Identity();
    //     auto r = R.block(0, 0, Eigen::fix<3>, Eigen::fix<3>);
    //     r = m_orientation.toRotationMatrix();

    //     Eigen::Matrix4f S = scale<float>(m_scale.x(), m_scale.y(), m_scale.z());
    //     m_local_matrix = T * R * S;
    //     return m_local_matrix;
    //   }

    // public:
    //   Transform() {}
    //   Transform(const Eigen::Matrix4f& transform) {
    //     m_position = transform.col(Eigen::fix<4>).head(Eigen::fix<3>);
    //     // Note that JacobiSVD is faster
    //     // than BDCSVD for small matrices.
    //     Eigen::JacobiSVD<Eigen::Matrix3f> svd(
    //         transform.block(Eigen::fix<0>, Eigen::fix<0>, Eigen::fix<3>, Eigen::fix<3>),
    //         Eigen::ComputeFullU | Eigen::ComputeFullV);

    //     float x = (svd.matrixU() * svd.matrixV().adjoint()).determinant() < 0
    //                   ? -1
    //                   : 1;  // so x has absolute value 1
    //     Eigen::Vector3f sv(svd.singularValues());
    //     sv.coeffRef(3 - 1) *= x;
    //     Eigen::Matrix3f scale = svd.matrixV() * sv.asDiagonal() * svd.matrixV().adjoint();
    //     Eigen::Matrix3f m(svd.matrixU());
    //     m.col(3 - 1) *= x;
    //     m_orientation = Eigen::Quaternionf{m * svd.matrixV().adjoint()};
    //     m_scale = scale.diagonal();
    //   }

    //   void compute_model_matrix() {
    //     m_model_matrix = get_local_matrix();
    //     m_is_dirty = false;
    //   }

    //   void compute_model_matrix(const Eigen::Matrix4f& parent_matrix) {
    //     m_model_matrix = parent_matrix * get_local_matrix();
    //     m_is_dirty = false;
    //   }

    //   const Eigen::Matrix4f& matrix() const { return m_model_matrix; }

    //   bool is_dirty() const { return m_is_dirty; }

    //   const Eigen::Vector3f get_local_position() const { return m_position; }
    //   const Eigen::Quaternionf get_local_orientation() const { return m_orientation; }

    //   Transform& set_local_position(const Eigen::Vector3f& pos) {
    //     m_position = pos;
    //     m_is_dirty = true;
    //     return *this;
    //   }
    //   Transform& set_local_orientation(const Eigen::Quaternionf& orient) {
    //     m_orientation = orient;
    //     m_is_dirty = true;
    //     return *this;
    //   }

    //   Transform& rotate(const Eigen::Quaternionf& rot) {
    //     m_orientation *= rot;
    //     m_is_dirty = true;
    //     return (*this);
    //   }
    //   Transform& rotate(const Eigen::Matrix3f& rot) {
    //     Eigen::Quaternionf R{rot};
    //     return rotate(R);
    //   }
    //   // Assume pure rotation matrix
    //   Transform& rotate(const Eigen::Matrix4f& rot) {
    //     Eigen::Quaternionf R{rot.block(Eigen::fix<0>, Eigen::fix<0>, Eigen::fix<3>,
    //     Eigen::fix<3>)}; return rotate(R);
    //   }
    //   Transform& rotate(const Eigen::AngleAxisf& rot) {
    //     Eigen::Quaternionf R{rot};
    //     return rotate(R);
    //   }

    //   Transform& translate(const Eigen::Vector3f& translation) {
    //     m_position += translation;
    //     m_is_dirty = true;
    //     return (*this);
    //   }
    //   Transform& translate(float x, float y, float z) {
    //     Eigen::Vector3f T{x, y, z};
    //     return translate(T);
    //   }

    //   Transform& rotate_x(float angle) {
    //     auto R = rotationX(angle);
    //     return rotate(R);
    //   }
    //   Transform& rotate_y(float angle) {
    //     auto R = rotationY(angle);
    //     return rotate(R);
    //   }
    //   Transform& rotate_z(float angle) {
    //     auto R = rotationZ(angle);
    //     return rotate(R);
    //   }

    //   friend Transform operator*(const Transform& lhs, const Transform& rhs);
    // };

    // Transform operator*(const Transform& lhs, const Transform& rhs) {
    //   return Transform{lhs.m_model_matrix * rhs.m_model_matrix};
    // }
  }  // namespace transform
}  // namespace yart
