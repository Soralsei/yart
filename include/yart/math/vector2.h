#include <iostream>
#include "yart/math/vector.h"

namespace yart {
  namespace vector {

    class Vector2 : VectorN<Vector2, 2> {
    public:
      Vector2();
      Vector2(float x, float y);

      float dot(const Vector2& other) const;

      static float dot(const Vector2& first, const Vector2& second);

      float angleBetween(const Vector2& other) const;
      void rotateArroundVector(const Vector2& axis, float rotation);
    };

  }  // namespace vector
}  // namespace yart
