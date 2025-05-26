#pragma once
#include "Eigen/Dense"
#include "yart/geometry/defines.h"

namespace yart {
  class Ray {
  private:
    // Eigen::Vector3f origin;
    // Eigen::Vector3f direction;
    Eigen::Vector4f origin;
    Eigen::Vector4f direction;

  public:
    Ray(Eigen::Vector3f _origin, Eigen::Vector3f _direction);
    Ray(Eigen::Vector4f _origin, Eigen::Vector4f _direction);
    Ray(Eigen::Vector3f _direction);
    ~Ray();

    const Eigen::Vector4f get_origin() const;
    const Eigen::Vector4f get_direction() const;

    Eigen::Vector4f position(double t) const;

    Ray transform(const geometry::Transform3D& transform) const;
    Ray transform(const Eigen::Matrix4f& transform) const;

    friend std::ostream& operator<<(std::ostream& out, const Ray& ray);
  };
}  // namespace yart
