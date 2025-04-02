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

      VectorN(float d[U]) {
        for (size_t i = 0; i < U; i++) {
          data[i] = d[i];
        }
      }

    public:
      VectorN() = default;
      float operator[](const int i) const { return data[i]; }

      SelfType& operator+=(float rhs) {
        for (size_t i = 0; i < U; i++) {
          data[i] += rhs;
        }
        return *this;
      }
      SelfType& operator-=(float rhs) {
        for (size_t i = 0; i < 3; i++) {
          data[i] -= rhs;
        }
        return *this;
      }

      SelfType& operator+=(const SelfType& rhs) {
        for (size_t i = 0; i < U; i++) {
          data[i] += rhs[i];
        }
        return *this;
      }
      SelfType& operator-=(const SelfType& rhs) {
        for (size_t i = 0; i < 3; i++) {
          data[i] -= rhs[i];
        }
        return *this;
      }

      SelfType& operator*=(float rhs) {
        for (size_t i = 0; i < 3; i++) {
          data[i] *= rhs;
        }
        return *this;
      }
      SelfType& operator/=(float rhs) {
        for (size_t i = 0; i < 3; i++) {
          data[i] /= rhs;
        }
        return *this;
      }

      SelfType& operator*=(const SelfType& rhs) {
        for (size_t i = 0; i < 3; i++) {
          data[i] *= rhs[i];
        }
        return *this;
      }
      SelfType& operator/=(const SelfType& rhs) {
        for (size_t i = 0; i < 3; i++) {
          data[i] /= rhs[i];
        }
        return *this;
      }

      friend SelfType operator+(const SelfType& lhs, float rhs);
      friend SelfType operator-(const SelfType& lhs, float rhs);

      friend SelfType operator+(const SelfType& lhs, const SelfType& rhs);
      friend SelfType operator-(const SelfType& lhs, const SelfType& rhs);

      friend SelfType operator*(const SelfType& lhs, float rhs);
      friend SelfType operator/(const SelfType& lhs, float rhs);

      friend SelfType operator*(const SelfType& lhs, const SelfType& rhs);
      friend SelfType operator/(const SelfType& lhs, const SelfType& rhs);

      friend bool operator==(const SelfType& lhs, const SelfType& rhs) {
        bool is_equal = true;
        for (size_t i = 0; i < U; i++)
        {
          is_equal |= math::approx_equals(lhs[i], rhs[i]);
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

      SelfType normalized() const { return (*this) / this->norm(); }
      SelfType abs() const {
        float d[U]{0};
        for (size_t i = 0; i < U; i++) {
          d[i] = data[i];
        }
        return SelfType{d};
      }
      // SelfType cross(const SelfType& other) const;
      // float dot(const SelfType& other) const;

      // static SelfType cross(const SelfType& first, const SelfType& second);
      // static float dot(const SelfType& first, const SelfType& second);

      // float angleBetween(const SelfType& other) const;
      // void rotateArroundVector(const SelfType& axis, float rotation);
    };

  }  // namespace vector

}  // namespace yart
