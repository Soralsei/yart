#pragma once

namespace yart {
  namespace vector {
    class Vector3 {
    public:
      // one way
      // float x = 0.0;
      // float y = 0.0;
      // float z = 0.0;

      // Another way
      float data[3] = {0, 0, 0};

      Vector3(float, float, float);

      float operator[](const int i) const;

      Vector3& operator+=(const int rhs);
      friend Vector3 operator+(Vector3& lhs, const int rhs);
      Vector3& operator-=(const int rhs);
      friend Vector3 operator-(Vector3& lhs, const int rhs);

      Vector3& operator+=(const Vector3& rhs);
      friend Vector3 operator+(Vector3& lhs, const Vector3& rhs);
      Vector3& operator-=(const Vector3& rhs);
      friend Vector3 operator-(Vector3& lhs, const Vector3& rhs);

      Vector3& operator*=(const Vector3& rhs);
      Vector3& operator*(const Vector3& rhs);
      Vector3& operator/=(const Vector3& rhs);
      Vector3& operator/(const Vector3& rhs);

      friend bool operator==(const Vector3& lhs, const Vector3& rhs);
      friend bool operator!=(const Vector3& lhs, const Vector3& rhs);

      float dot(const Vector3& other);
      float cross(const Vector3& other);
      Vector3 abs() const;
      float norm() const;
      Vector3 normalized() const;

      float angleBetween(const Vector3& other) const;
      void rotateArroundVector(const Vector3& axis, float rotation);
    };

    extern Vector3 ZERO;
    extern Vector3 ONE;
  }  // namespace vector
}  // namespace yart