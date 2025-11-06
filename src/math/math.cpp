#include "yart/util/math.hpp"

#include <cmath>
#include <glm/geometric.hpp>

namespace yart {

  namespace math {

    glm::vec4 reflect(const glm::vec4& vector, const glm::vec4& normal) {
      return vector - normal * 2.0f * glm::dot(vector, normal);
    }

  }  // namespace math

}  // namespace yart