#include "yart/math/vector2.h"

namespace yart {
  namespace vector {
    const Vector2 Vector2::ZERO{0, 0};
    const Vector2 Vector2::ONE{1, 1};
    const Vector2 Vector2::UP{0, 1};
    const Vector2 Vector2::DOWN{0, -1};
    const Vector2 Vector2::LEFT{-1, 0};
    const Vector2 Vector2::RIGHT{1, 0};

    Vector2::Vector2(float x, float y) {
      data[0] = x;
      data[1] = y;
    }

    Vector2::Vector2(float d[2]) : VectorN<Vector2, 2>(d) {}
    Vector2::Vector2(const VectorN<Vector2, 2> &v) {
      for (int i = 0; i < 2; i++) {
        data[i] = v[i];
      }
    }

    template <> Vector2 operator+(const Vector2 &lhs, float rhs) {
      return Vector2{lhs[0] + rhs, lhs[1] + rhs};
    }

    template <> Vector2 operator+(const Vector2 &lhs, const Vector2 &rhs) {
      return Vector2{lhs[0] + rhs[0], lhs[1] + rhs[1]};
    }

    template <> Vector2 operator-(const Vector2 &lhs, float rhs) {
      return Vector2{lhs[0] - rhs, lhs[1] - rhs};
    }

    template <> Vector2 operator-(const Vector2 &lhs, const Vector2 &rhs) {
      return Vector2{lhs[0] - rhs[0], lhs[1] - rhs[1]};
    }

    template <> Vector2 operator*(const Vector2 &lhs, float rhs) {
      return Vector2{lhs[0] * rhs, lhs[1] * rhs};
    }

    template <> Vector2 operator*(const Vector2 &lhs, const Vector2 &rhs) {
      return Vector2{lhs[0] * rhs[0], lhs[1] * rhs[1]};
    }

    template <> Vector2 operator/(const Vector2 &lhs, float rhs) {
      return Vector2{lhs[0] / rhs, lhs[1] / rhs};
    }

    template <> Vector2 operator/(const Vector2 &lhs, const Vector2 &rhs) {
      return Vector2{lhs[0] / rhs[0], lhs[1] / rhs[1]};
    }
  }  // namespace vector

}  // namespace yart
