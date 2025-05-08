#include "yart/math/math.h"

#include <cmath>
#include <type_traits>

namespace yart {

  namespace math {

    Eigen::Vector3f reflect(const Eigen::Vector3f& vector, const Eigen::Vector3f& normal) {
      return vector - normal * 2 * vector.dot(normal);
    }

  }  // namespace math
  
}  // namespace yart