#pragma once
#include <cmath>
#include "Eigen/Dense"

namespace yart {
  namespace transform {
    template <typename T> Eigen::Matrix4<T> translation(T x, T y, T z) {
      Eigen::Matrix4<T> m;
      m << 1, 0, 0, x,
           0, 1, 0, y,
           0, 0, 1, z,
           0, 0, 0, 1;
      return m;
    }

    template <typename T> Eigen::Matrix4<T> scaling(T x, T y, T z) {
      Eigen::Matrix4<T> m;
      m << x, 0, 0, 0,
           0, y, 0, 0,
           0, 0, z, 0,
           0, 0, 0, 1;
      return m;
    }

    template <typename T> Eigen::Matrix4<T> rotationX(T theta) {
      Eigen::Matrix4<T> m;
      m << 1, 0, 0, 0,
           0, std::cos(theta), -std::sin(theta), 0,
           0, std::sin(theta), std::cos(theta), 0,
           0, 0, 0, 1;
      return m;
    }
    
    template <typename T> Eigen::Matrix4<T> rotationY(T theta) {
      Eigen::Matrix4<T> m;
      m << std::cos(theta), 0, std::sin(theta), 0,
           0, 1, 0, 0,
           -std::sin(theta), 0, std::cos(theta), 0,
           0, 0, 0, 1;
      return m;
    }

    template <typename T> Eigen::Matrix4<T> rotationZ(T theta) {
      Eigen::Matrix4<T> m;
      m << std::cos(theta), -std::sin(theta), 0, 0,
           std::sin(theta), std::cos(theta), 0, 0,
           0, 0, 1, 0,
           0, 0, 0, 1;
      return m;
    }

    template<typename T> Eigen::Matrix4<T> shear(T xy, T xz, T yx, T yz, T zx, T zy) {
      Eigen::Matrix4<T> m;
      m << 1, xy, xz, 0,
           yx, 1, yz, 0,
           zx, zy, 1, 0,
           0,  0,  0, 1;
      return m;
    }
  }  // namespace transform
}  // namespace yart
