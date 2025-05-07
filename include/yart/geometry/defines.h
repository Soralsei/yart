#pragma once
#include <Eigen/Dense>
#include <Eigen/Geometry>

namespace yart
{
  namespace geometry
  {
    using Transform3d = Eigen::Affine3f;
    using Quaternion = Eigen::Quaternionf;
  } // namespace geometry
} // namespace yart
