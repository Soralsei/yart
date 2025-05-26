#include "yart/util/math.h"

#include <cmath>
#include <type_traits>

namespace yart {

  namespace math {

    Eigen::Vector4f reflect(const Eigen::Vector4f& vector, const Eigen::Vector4f& normal) {
      return vector - normal * 2 * vector.dot(normal);
    }

  }  // namespace math
  
}  // namespace yart