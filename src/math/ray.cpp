
#include "yart/math/ray.h"
using namespace Eigen;
namespace yart {
  Ray::Ray(Eigen::Vector4f _origin, Eigen::Vector4f _direction)
      : origin(_origin), direction(_direction) {}
  Ray::Ray(Eigen::Vector4f _direction) : origin(Vector4f{0, 0, 0, 1}), direction(_direction) {}
  Ray::~Ray() {}

  Eigen::Vector4f Ray::position(double t) { return origin + direction * t; }
  const Eigen::Vector4f& Ray::get_direction() const { return direction; }
  const Eigen::Vector4f& Ray::get_origin() const { return origin; }
}  // namespace yart
