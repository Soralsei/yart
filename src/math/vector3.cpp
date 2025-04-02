#include "yart/math/vector3.h"

#include "yart/math/math.h"

// #include <cstdlib>

namespace yart {
  namespace vector {
    const Vector3 Vector3::ZERO = {0, 0, 0};
    const Vector3 Vector3::ONE = {1, 1, 1};
    const Vector3 Vector3::UP = {0, 1, 0};
    const Vector3 Vector3::DOWN = {0, -1, 0};
    const Vector3 Vector3::LEFT = {-1, 0, 0};
    const Vector3 Vector3::RIGHT = {1, 0, 0};
    const Vector3 Vector3::FORWARD = {0, 0, 1};
    const Vector3 Vector3::BACKWARD = {0, 0, -1};

    Vector3::Vector3(float x, float y, float z) {
      data[0] = x;
      data[1] = y;
      data[2] = z;
    }

    float Vector3::operator[](const int i) const { return data[i]; }

    bool operator==(const Vector3& lhs, const Vector3& rhs) {
      return math::approx_equals(lhs[0], rhs[0]) && math::approx_equals(lhs[1], rhs[1])
             && math::approx_equals(lhs[2], rhs[2]);
    }

    bool operator!=(const Vector3& lhs, const Vector3& rhs) { return !(lhs == rhs); }

    // ADDITION / SUBTRACTION ######################################################################
    Vector3& Vector3::operator+=(float rhs) {
      for (size_t i = 0; i < 3; i++) {
        data[i] += rhs;
      }
      return *this;
    }
    Vector3& Vector3::operator+=(const Vector3& rhs) {
      for (size_t i = 0; i < 3; i++) {
        data[i] += rhs[i];
      }
      return *this;
    }
    Vector3 operator+(const Vector3& lhs, float rhs) {
      return Vector3(lhs[0] + rhs, lhs[1] + rhs, lhs[2] + rhs);
    }
    Vector3 operator+(const Vector3& lhs, const Vector3& rhs) {
      return Vector3(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]);
    }

    Vector3& Vector3::operator-=(float rhs) {
      for (size_t i = 0; i < 3; i++) {
        data[i] -= rhs;
      }
      return *this;
    }
    Vector3& Vector3::operator-=(const Vector3& rhs) {
      for (size_t i = 0; i < 3; i++) {
        data[i] -= rhs[i];
      }
      return *this;
    }
    Vector3 operator-(const Vector3& lhs, float rhs) {
      return Vector3(lhs[0] - rhs, lhs[1] - rhs, lhs[2] - rhs);
    }
    Vector3 operator-(const Vector3& lhs, const Vector3& rhs) {
      return Vector3(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]);
    }
    // #############################################################################################

    // MULTIPLICATION / DIVISION ###################################################################
    Vector3& Vector3::operator*=(float rhs) {
      for (size_t i = 0; i < 3; i++) {
        data[i] *= rhs;
      }
      return *this;
    }
    Vector3& Vector3::operator*=(const Vector3& rhs) {
      for (size_t i = 0; i < 3; i++) {
        data[i] *= rhs[i];
      }
      return *this;
    }
    Vector3 operator*(const Vector3& lhs, float rhs) {
      return Vector3(lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs);
    }
    Vector3 operator*(const Vector3& lhs, const Vector3& rhs) {
      return Vector3(lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2]);
    }

    Vector3& Vector3::operator/=(float rhs) {
      for (size_t i = 0; i < 3; i++) {
        data[i] /= rhs;
      }
      return *this;
    }
    Vector3& Vector3::operator/=(const Vector3& rhs) {
      for (size_t i = 0; i < 3; i++) {
        data[i] /= rhs[i];
      }
      return *this;
    }
    Vector3 operator/(const Vector3& lhs, float rhs) {
      return Vector3(lhs[0] / rhs, lhs[1] / rhs, lhs[2] / rhs);
    }
    Vector3 operator/(const Vector3& lhs, const Vector3& rhs) {
      return Vector3(lhs[0] / rhs[0], lhs[1] / rhs[1], lhs[2] / rhs[2]);
    }

    std::ostream& operator<<(std::ostream& outs, const Vector3& vec) {
      outs << "Vector3(" << vec[0] << ", " << vec[1] << ", " << vec[2] << ")";
      return outs;
    }
    // #############################################################################################

    float Vector3::norm() const {
      float res = 0;
      for (size_t i = 0; i < 3; i++) {
        res += data[i] * data[i];
      }
      return std::sqrt(res);
    }

    Vector3 Vector3::abs() const {
      return Vector3(std::abs(data[0]), std::abs(data[1]), std::abs(data[2]));
    }

    Vector3 Vector3::normalized() const {
      float n = norm();
      if (n == 0) {
        return ZERO;
      }
      return *this / n;
    }

    float Vector3::dot(const Vector3& other) const {
      float ret = 0.0;
      for (size_t i = 0; i < 3; i++) {
        ret += data[i] * other[i];
      }
      return ret;
    }

    Vector3 Vector3::cross(const Vector3& other) const {
      return Vector3(data[1] * other[2] - data[2] * other[1],
                     data[2] * other[0] - data[0] * other[2],
                     data[0] * other[1] - data[1] * other[0]);
    }

    float Vector3::dot(const Vector3& first, const Vector3& second) { return first.dot(second); }

    Vector3 Vector3::cross(const Vector3& first, const Vector3& second) {
      return first.cross(second);
    }

  }  // namespace vector
}  // namespace yart