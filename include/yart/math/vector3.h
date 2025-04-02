#pragma once
#include <ostream>

namespace yart {
  namespace vector {
    class Vector3 {
    public:
      static const Vector3 ZERO;
      static const Vector3 ONE;
      static const Vector3 UP;
      static const Vector3 DOWN;
      static const Vector3 LEFT;
      static const Vector3 RIGHT;
      static const Vector3 FORWARD;
      static const Vector3 BACKWARD;
      // one way
      // float x = 0.0;
      // float y = 0.0;
      // float z = 0.0;

      // Another way
      float data[3] = {0};

      Vector3(float, float, float);

      float operator[](const int i) const;

      Vector3& operator+=(float rhs);
      friend Vector3 operator+(const Vector3& lhs, float rhs);
      Vector3& operator-=(float rhs);
      friend Vector3 operator-(const Vector3& lhs, float rhs);

      Vector3& operator+=(const Vector3& rhs);
      friend Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
      Vector3& operator-=(const Vector3& rhs);
      friend Vector3 operator-(const Vector3& lhs, const Vector3& rhs);

      Vector3& operator*=(float rhs);
      friend Vector3 operator*(const Vector3& lhs, float rhs);
      Vector3& operator/=(float rhs);
      friend Vector3 operator/(const Vector3& lhs, float rhs);

      Vector3& operator*=(const Vector3& rhs);
      friend Vector3 operator*(const Vector3& lhs, const Vector3& rhs);
      Vector3& operator/=(const Vector3& rhs);
      friend Vector3 operator/(const Vector3& lhs, const Vector3& rhs);

      friend bool operator==(const Vector3& lhs, const Vector3& rhs);
      friend bool operator!=(const Vector3& lhs, const Vector3& rhs);

      friend std::ostream& operator<<(std::ostream& outs, const Vector3& vec);

      float norm() const;
      Vector3 normalized() const;
      Vector3 abs() const;
      Vector3 cross(const Vector3& other) const;
      float dot(const Vector3& other) const;

      static Vector3 cross(const Vector3& first, const Vector3& second);
      static float dot(const Vector3& first, const Vector3& second);

      float angleBetween(const Vector3& other) const;
      void rotateArroundVector(const Vector3& axis, float rotation);
    };
  }  // namespace vector
}  // namespace yart