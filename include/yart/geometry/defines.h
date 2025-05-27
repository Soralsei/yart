#pragma once
#include <Eigen/Dense>
#include <Eigen/Geometry>

namespace yart {
  namespace geometry {
    using Transform3D = Eigen::Affine3f;
    using Quaternion = Eigen::Quaternionf;

    constexpr double SHADOW_EPSILON = 1e-3;
    constexpr double EPSILON = 1e-6;
  }  // namespace geometry
}  // namespace yart
