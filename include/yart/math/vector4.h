#pragma once
#include "yart/math/vector.h"

namespace yart {
  namespace vector {

    class Vector4 : public VectorN<Vector4, 4> {
    public:
      static const Vector4 ZERO;
      static const Vector4 ONE;

      Vector4();
      Vector4(float x, float y, float z, float w);
      Vector4(float d[4]);
      Vector4(const VectorN<Vector4, 4> &v);

      float angleBetween(const Vector4& other) const;
      void rotateArroundVector(const Vector4& axis, float rotation);
    };

  }  // namespace vector
}  // namespace yart
