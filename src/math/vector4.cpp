#include "yart/math/vector4.h"

namespace yart {
  namespace vector {
    const Vector4 Vector4::ZERO{0, 0, 0, 0};
    const Vector4 Vector4::ONE{1, 1, 1, 1};

    Vector4::Vector4(float x, float y, float z, float w) {
      data[0] = x;
      data[1] = y;
      data[2] = z;
      data[3] = w;
    }

    Vector4::Vector4(float d[4]) : VectorN<Vector4, 4>(d) {}
    Vector4::Vector4(const VectorN<Vector4, 4> &v) {
      for (int i = 0; i < 4; i++) {
        data[i] = v[i];
      }
    }

    template <> Vector4 operator+(const Vector4 &lhs, float rhs) {
      return Vector4{lhs[0] + rhs, lhs[1] + rhs, lhs[2] + rhs, lhs[3] + rhs};
    }

    template <> Vector4 operator+(const Vector4 &lhs, const Vector4 &rhs) {
      return Vector4{lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2], lhs[3] + rhs[3]};
    }

    template <> Vector4 operator-(const Vector4 &lhs, float rhs) {
      return Vector4{lhs[0] - rhs, lhs[1] - rhs, lhs[2] - rhs, lhs[3] - rhs};
    }

    template <> Vector4 operator-(const Vector4 &lhs, const Vector4 &rhs) {
      return Vector4{lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2], lhs[3] - rhs[3]};
    }

    template <> Vector4 operator*(const Vector4 &lhs, float rhs) {
      return Vector4{lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs, lhs[3] * rhs};
    }

    template <> Vector4 operator*(const Vector4 &lhs, const Vector4 &rhs) {
      return Vector4{lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2], lhs[3] * rhs[3]};
    }

    template <> Vector4 operator/(const Vector4 &lhs, float rhs) {
      return Vector4{lhs[0] / rhs, lhs[1] / rhs, lhs[2] / rhs, lhs[3] / rhs};
    }

    template <> Vector4 operator/(const Vector4 &lhs, const Vector4 &rhs) {
      return Vector4{lhs[0] / rhs[0], lhs[1] / rhs[1], lhs[2] / rhs[2], lhs[3] / rhs[3]};
    }
  }  // namespace vector

}  // namespace yart
