#pragma once
#include "Eigen/Dense"

namespace yart {
  class Ray {
  private:
    Eigen::Vector4f origin;
    Eigen::Vector4f direction;

  public:
    Ray(Eigen::Vector4f _origin, Eigen::Vector4f _direction);
    Ray(Eigen::Vector4f _direction);
    ~Ray();

    const Eigen::Vector4f& get_origin() const;
    const Eigen::Vector4f& get_direction() const;

    Eigen::Vector4f position(double t);
  };
}  // namespace yart
