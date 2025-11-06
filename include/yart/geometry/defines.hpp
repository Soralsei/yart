#pragma once
#include "yart/geometry/transform.hpp"

namespace yart {
  namespace geometry {
    using Transform = transform::Transform;

    constexpr double SHADOW_EPSILON = 1e-3;
    constexpr double EPSILON = 1e-6;
  }  // namespace geometry
}  // namespace yart
