#include "yart/core/ray.h"

#include <iostream>

using namespace Eigen;
namespace yart {

  Ray::Ray(Eigen::Vector3f _origin, Eigen::Vector3f _direction) {
    origin = Eigen::Vector4f{_origin.x(), _origin.y(), _origin.z(), 1.0f};
    direction = Eigen::Vector4f{_direction.x(), _direction.y(), _direction.z(), 0.0f};
  }

  Ray::Ray(Eigen::Vector4f _origin, Eigen::Vector4f _direction)
      : origin(_origin), direction(_direction) {}

  Ray::Ray(Eigen::Vector3f _direction) : Ray::Ray(Vector3f::Zero(), _direction) {}

  Ray::~Ray() {}

  Eigen::Vector4f Ray::position(double t) const { return origin + direction * t; }
  const Eigen::Vector4f Ray::get_direction() const { return direction; }
  const Eigen::Vector4f Ray::get_origin() const { return origin; }

  Ray Ray::transform(const geometry::Transform3D& T) const { return transform(T.matrix()); }

  Ray Ray::transform(const Eigen::Matrix4f& transform) const {
    // std::cout << "Transform :\n" << transform << "\n";
    Eigen::Vector4f origin_transformed = transform * origin;
    Eigen::Vector4f direction_transformed = transform * direction;

    Ray transformed_ray{origin_transformed, direction_transformed};

    return transformed_ray;
  }

  std::ostream& operator<<(std::ostream& out, const Ray& ray) {
    out << "Ray(origin: [" << ray.get_origin().transpose() << "], direction: ["
        << ray.get_direction().transpose() << "])";
    return out;
  }
}  // namespace yart
