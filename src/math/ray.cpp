
#include "yart/math/ray.h"
using namespace Eigen;
namespace yart {

  Ray::Ray(Eigen::Vector3f _origin, Eigen::Vector3f _direction)
      : origin(_origin), direction(_direction) {
    origin_homogeneous = {origin.x(), origin.y(), origin.z(), 1.0f};
    direction_homogeneous = {direction.x(), direction.y(), direction.z(), 0.0f};
  }

  Ray::Ray(Eigen::Vector3f _direction) : Ray::Ray(Vector3f{0, 0, 0}, _direction) {}

  Ray::~Ray() {}

  Eigen::Vector3f Ray::position(double t) {
    auto result = origin + direction * t;
    return result.head<3>();
  }
  const Eigen::Vector3f Ray::get_direction() const { return direction; }
  const Eigen::Vector3f Ray::get_origin() const { return origin; }
  const Eigen::Vector4f Ray::get_direction_homogeneous() const { return direction_homogeneous; }
  const Eigen::Vector4f Ray::get_origin_homogeneous() const { return origin_homogeneous; }

  Ray Ray::operator*(const geometry::Transform3d& transform) const {
    return (*this) * transform.matrix();
  }

  Ray Ray::operator*(const Eigen::Matrix4f& transform) const {
    Eigen::Vector4f origin_transformed = transform * origin_homogeneous;
    Eigen::Vector4f direction_transformed = transform * direction_homogeneous;

    Ray transformed_ray{origin_transformed.head<3>(), direction_transformed.head<3>()};

    return transformed_ray;
  }

  std::ostream& operator<<(std::ostream& out, const Ray& ray) {
    out << "Ray(origin: [" << ray.get_origin().transpose() << "], direction: [" << ray.get_direction().transpose()
        << "])";
    return out;
  }
}  // namespace yart
