#pragma once

#include <cmath>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <stdexcept>
#include <type_traits>

namespace yart {
  namespace math {
    constexpr double ATOL = 1e-8;
    constexpr double RTOL = 1e-5;
    constexpr double TAU = M_PI * 2;

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

    // Function to remap a value from one range to another
    // This function takes a value and remaps it from the range [old_min, old_max]
    // to the range [new_min, new_max].
    template <typename T, typename U> U remap(T value, T old_min, T old_max, U new_min, U new_max) {
      static_assert(std::is_arithmetic_v<T>, "remap: Invalid type T, not arithmetic");
      if (old_min == old_max) {
        throw std::invalid_argument("remap: old_min and old_max cannot be equal");
      }
      if (new_min == new_max) {
        throw std::invalid_argument("remap: new_min and new_max cannot be equal");
      }
      if (value < old_min || value > old_max) {
        throw std::out_of_range("remap: value is out of range");
      }
      if (old_min > old_max) {
        std::swap(old_min, old_max);
      }
      if (new_min > new_max) {
        std::swap(new_min, new_max);
      }
      return (value - old_min) / static_cast<U>(old_max - old_min) * (new_max - new_min) + new_min;
    }

    glm::vec4 reflect(const glm::vec4& vector, const glm::vec4& normal);

  }  // namespace math
}  // namespace yart