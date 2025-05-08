#include "yart/geometry/sphere.h"

#include <iostream>

#include "yart/geometry/intersection.h"
#include "yart/math/ray.h"
#include "yart/util/vector.h"

namespace yart {

  namespace geometry {

    Sphere::Sphere(Transform3d _transform, float _radius)
        : Shape<Sphere>::Shape(_transform), radius(_radius) {}

    Sphere::Sphere(Eigen::Vector3f _position, float _radius)
        : Shape<Sphere>::Shape(_position), radius(_radius) {}

    Sphere::Sphere(float _radius) : Shape<Sphere>::Shape(), radius(_radius) {}
    Sphere::Sphere() : Shape<Sphere>::Shape(), radius(1.0f) {}

    Sphere::~Sphere() {}

    std::vector<Intersection<Sphere>> Sphere::intersections(const yart::Ray& ray) {
      // Transform the ray to the local space of the shape
      auto transformed_ray = ray * transform.inverse();
      Eigen::Vector3f self_to_ray = transformed_ray.get_origin() - position();
      auto direction = transformed_ray.get_direction();
      float a = direction.dot(direction);
      float b = 2 * direction.dot(self_to_ray);
      float c = self_to_ray.dot(self_to_ray) - radius * radius;

      float delta = b * b - 4 * a * c;

      // No intersections
      if (delta < 0) {
        return std::vector<Intersection<Sphere>>{};
      }
      Intersection<Sphere> i1 = {this->weak_from_this(), (-b - std::sqrt(delta)) / (2 * a)};
      Intersection<Sphere> i2 = {this->weak_from_this(), (-b + std::sqrt(delta)) / (2 * a)};
      // Return 2 intersections whether ray is tangent or not
      return make_vec(i1, i2);
    }

    std::ostream& operator<<(std::ostream& out, const Sphere& sphere) {
      return out << "Sphere([" << sphere.position().x() << ", " << sphere.position().y() << ", "
                 << sphere.position().z() << "], radius: " << sphere.radius << ")";
    }

  }  // namespace geometry

}  // namespace yart
