#pragma once
#include "yart/math/vector.h"

namespace yart {
  namespace vector {

    class Vector2 : public VectorN<Vector2, 2> {
    public:
      static const Vector2 ZERO;
      static const Vector2 ONE;
      static const Vector2 UP;
      static const Vector2 DOWN;
      static const Vector2 LEFT;
      static const Vector2 RIGHT;

      Vector2();
      Vector2(float x, float y);
      Vector2(float d[2]);
      Vector2(const VectorN<Vector2, 2> &v);

      float angleBetween(const Vector2& other) const;
      void rotateArroundVector(const Vector2& axis, float rotation);
    };

  }  // namespace vector
}  // namespace yart
