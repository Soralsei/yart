#pragma once
#include <cstddef>
#include <iostream>

#include "yart/math/math.h"

namespace yart {
  namespace vector {
    // template <class SelfType, size_t U> class VectorN;

    template <class SelfType> SelfType operator+(const SelfType& lhs, float rhs);
    template <class SelfType> SelfType operator-(const SelfType& lhs, float rhs);
    template <class SelfType> SelfType operator+(const SelfType& lhs, const SelfType& rhs);
    template <class SelfType> SelfType operator-(const SelfType& lhs, const SelfType& rhs);
    template <class SelfType> SelfType operator*(const SelfType& lhs, float rhs);
    template <class SelfType> SelfType operator/(const SelfType& lhs, float rhs);
    template <class SelfType> SelfType operator*(const SelfType& lhs, const SelfType& rhs);
    template <class SelfType> SelfType operator/(const SelfType& lhs, const SelfType& rhs);

    template <class SelfType, size_t U> class VectorN {
    protected:
      float data[U];

    public:
      VectorN() = default;
      VectorN<SelfType, U>(float d[U]) {
        for (size_t i = 0; i < U; i++) {
          data[i] = d[i];
        }
      }
      float operator[](const int i) const { return data[i]; }

      auto operator+=(float rhs) {
        for (size_t i = 0; i < U; i++) {
          data[i] += rhs;
        }
        return *this;
      }

      auto operator-=(float rhs) {
        for (size_t i = 0; i < U; i++) {
          data[i] -= rhs;
        }
        return *this;
      }

      auto operator+=(const SelfType& rhs) {
        for (size_t i = 0; i < U; i++) {
          data[i] += rhs[i];
        }
        return *this;
      }
      auto operator-=(const SelfType& rhs) {
        for (size_t i = 0; i < U; i++) {
          data[i] -= rhs[i];
        }
        return *this;
      }

      auto operator*=(float rhs) {
        for (size_t i = 0; i < U; i++) {
          data[i] *= rhs;
        }
        return *this;
      }
      auto operator/=(float rhs) {
        for (size_t i = 0; i < U; i++) {
          data[i] /= rhs;
        }
        return *this;
      }

      auto operator*=(const SelfType& rhs) {
        for (size_t i = 0; i < U; i++) {
          data[i] *= rhs[i];
        }
        return *this;
      }
      auto operator/=(const SelfType& rhs) {
        for (size_t i = 0; i < U; i++) {
          data[i] /= rhs[i];
        }
        return *this;
      }

      friend SelfType operator+ <>(const SelfType& lhs, float rhs);
      friend SelfType operator- <>(const SelfType& lhs, float rhs);

      friend SelfType operator+ <>(const SelfType& lhs, const SelfType& rhs);
      friend SelfType operator- <>(const SelfType& lhs, const SelfType& rhs);

      friend SelfType operator* <>(const SelfType& lhs, float rhs);
      friend SelfType operator/ <>(const SelfType& lhs, float rhs);

      friend SelfType operator* <>(const SelfType& lhs, const SelfType& rhs);
      friend SelfType operator/ <>(const SelfType& lhs, const SelfType& rhs);

      friend bool operator==(const SelfType& lhs, const SelfType& rhs) {
        bool is_equal = true;
        for (size_t i = 0; i < U; i++) {
          is_equal &= math::approx_equals(lhs[i], rhs[i]);
        }
        return is_equal;
      }
      friend bool operator!=(const SelfType& lhs, const SelfType& rhs) { return !(lhs == rhs); }

      friend std::ostream& operator<<(std::ostream& outs, const SelfType& vec) {
        outs << "Vector" << U << "(";
        for (size_t i = 0; i < U - 1; i++) {
          outs << vec[i] << ", ";
        }
        outs << vec[U - 1] << ")\n";
        return outs;
      }

      float norm() const {
        float res = 0.0f;
        for (size_t i = 0; i < U; i++) {
          res += data[i] * data[i];
        }
        return std::sqrt(res);
      }

      SelfType normalized() const {
        float norm = this->norm();
        if (norm == 0) {
          float d[U]{0};
          return static_cast<SelfType>(VectorN{d});
        }
        SelfType v = static_cast<SelfType>(*this);
        return v / norm;
      }

      SelfType abs() const {
        float d[U]{0};
        for (size_t i = 0; i < U; i++) {
          d[i] = std::abs(data[i]);
        }
        return SelfType{d};
      }
      // SelfType cross(const SelfType& other) const;
      float dot(const SelfType& other) const {
        float res = 0;
        for (size_t i = 0; i < U; i++) {
          res += data[i] * other[i];
        }
        return res;
      }

      // static SelfType cross(const SelfType& first, const SelfType& second);
      static float dot(const SelfType& first, const SelfType& second) { return first.dot(second); }

      // float angleBetween(const SelfType& other) const;
      // void rotateArroundVector(const SelfType& axis, float rotation);
    };

  }  // namespace vector

}  // namespace yart
