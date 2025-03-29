#pragma once

namespace yart
{
  constexpr double ATOL = 1e-8;
  constexpr double RTOL = 1e-5;

  template<typename T>
  bool approx_equals(T left, T right, double atol = ATOL, double rtol = RTOL);
}  // namespace yart