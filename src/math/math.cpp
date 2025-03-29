#include "yart/math/math.h"

#include <cmath>
#include <type_traits>

namespace yart
{
    template<typename T>
    bool approx_equals(T left, T right, double atol, double rtol)
    {
        static_assert(std::is_floating_point_v<T>, "Approx equals requires that both numbers are floating point");
        return std::abs(left - right) <= std::max(rtol * std::max(std::abs(left), std::abs(right)), atol);
    }
}  // namespace yart