#pragma once
#include <cmath>

namespace yart {
  namespace math {
    constexpr double ATOL = 1e-8;
    constexpr double RTOL = 1e-5;
    constexpr double TAU = 6.28318530717958647692;

    // Function to compare two floating point numbers for approximate equality
    // This function uses a relative tolerance (rtol) and an absolute tolerance (atol)
    // to determine if two numbers are approximately equal.
    // The default values for atol and rtol are set to 1e-8 and 1e-5 respectively.
    template <typename T>
    bool approx_equals(T left, T right, double atol = ATOL, double rtol = RTOL) {
      static_assert(std::is_floating_point_v<T>,
                    "Approx equals requires that both numbers are floating point");
      return std::abs(left - right)
             <= std::max(rtol * std::max(std::abs(left), std::abs(right)), atol);
    }
  }  // namespace math
}  // namespace yart