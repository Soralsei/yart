#include "yart/math/vector3.h"

#include <cstdlib>

namespace yart {
  namespace vector {
    Vector3 ZERO = {0, 0, 0};
    Vector3 ONE = {1, 1, 1};

    Vector3::Vector3(float x, float y, float z) {
      data[0] = x;
      data[1] = y;
      data[2] = z;
    }

    float Vector3::operator[](const int i) const { return data[i]; }

    bool operator==(const Vector3& lhs, const Vector3& rhs) {
      return lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2];
    }

    bool operator!=(const Vector3& lhs, const Vector3& rhs) { return !(lhs == rhs); }
  }  // namespace vector
}  // namespace yart