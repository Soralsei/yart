#pragma once
#include <cmath>
#include "Eigen/Dense"
#include "Eigen/Geometry"

namespace yart {
  namespace transform {
    template <typename T> Eigen::Translation<T, 3> translation(T x, T y, T z) {
      return Eigen::Translation<T, 3> {x, y, z};
      // Eigen::Matrix3<T> m;
      // m << 1, 0, 0, x,
      //      0, 1, 0, y,
      //      0, 0, 1, z,
      //      0, 0, 0, 1;
      // return m;
    }

    template <typename T> auto scaling(T x, T y, T z) {
      return Eigen::Scaling(x, y, z);
      // Eigen::Matrix3<T> m;
      // m << x, 0, 0, 0,
      //      0, y, 0, 0,
      //      0, 0, z, 0,
      //      0, 0, 0, 1;
      // return m;
    }

    template <typename T> Eigen::Matrix3<T> rotationX(T theta) {
      Eigen::Matrix3<T> m;
      m << 1, 0, 0,
           0, std::cos(theta), -std::sin(theta),
           0, std::sin(theta), std::cos(theta);
      return m;
    }
    
    template <typename T> Eigen::Matrix3<T> rotationY(T theta) {
      Eigen::Matrix3<T> m;
      m << std::cos(theta), 0, std::sin(theta),
           0, 1, 0,
           -std::sin(theta), 0, std::cos(theta);
      return m;
    }

    template <typename T> Eigen::Matrix3<T> rotationZ(T theta) {
      Eigen::Matrix3<T> m;
      m << std::cos(theta), -std::sin(theta), 0,
           std::sin(theta), std::cos(theta), 0,
           0, 0, 1;
      return m;
    }

    template<typename T> Eigen::Matrix3<T> shear(T xy, T xz, T yx, T yz, T zx, T zy) {
      Eigen::Matrix3<T> m;
      m << 1, xy, xz,
           yx, 1, yz,
           zx, zy, 1;
      return m;
    }
  }  // namespace transform
}  // namespace yart
