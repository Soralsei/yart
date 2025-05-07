#pragma once
#include "Eigen/Dense"
#include "yart/geometry/defines.h"

namespace yart {
  class Ray {
  private:
    Eigen::Vector3f origin;
    Eigen::Vector3f direction;
    Eigen::Vector4f origin_homogeneous;
    Eigen::Vector4f direction_homogeneous;

  public:
    Ray(Eigen::Vector3f _origin, Eigen::Vector3f _direction);
    Ray(Eigen::Vector3f _direction);
    ~Ray();

    const Eigen::Vector3f get_origin() const;
    const Eigen::Vector3f get_direction() const;
    const Eigen::Vector4f get_origin_homogeneous() const;
    const Eigen::Vector4f get_direction_homogeneous() const;

    Eigen::Vector3f position(double t);

    Ray operator*(const geometry::Transform3d& transform) const;
    Ray operator*(const Eigen::Matrix4f& transform) const;
    // Ray operator*(geometry::Transform3d& transform);
    // Ray operator*(Eigen::Matrix4f& transform);

    friend std::ostream& operator<<(std::ostream& out, const Ray& ray);
  };
}  // namespace yart
