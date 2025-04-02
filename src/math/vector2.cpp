#include "yart/math/vector2.h"

namespace yart
{
  namespace vector
  {
    Vector2::Vector2(float x, float y) {
      data[0] = x;
      data[1] = y;
    }

    template<>
    Vector2 operator+(Vector2 lhs, float rhs) {
      return Vector2 {0, 0};
    }
  } // namespace vector
  
} // namespace yart
