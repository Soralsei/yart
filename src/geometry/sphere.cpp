#include <iostream>

#include "yart/geometry/intersection.h"
#include "yart/geometry/sphere.h"
#include "yart/math/ray.h"
#include "yart/util/vector.h"

namespace yart {

  namespace geometry {

    Sphere::Sphere(Eigen::Vector4f _origin, float _radius)
        : Shape<Sphere>::Shape(_origin), radius(_radius) {}

    Sphere::Sphere(float _radius)
        : Shape<Sphere>::Shape(Eigen::Vector4f{0, 0, 0, 1}), radius(_radius) {}

    Sphere::~Sphere() {}

    std::vector<Intersection<Sphere>> Sphere::intersections(const yart::Ray& ray) {
      auto self_to_ray = ray.get_origin() - origin;
      auto direction = ray.get_direction();
      float a = direction.dot(direction);
      float b = 2 * direction.dot(self_to_ray);
      float c = self_to_ray.dot(self_to_ray) - radius * radius;

      float delta = b * b - 4 * a * c;

      std::cout << "self_to_ray : " << self_to_ray << "\n";

      std::cout << "a : " << a << "\n";
      std::cout << "b : " << b << "\n";
      std::cout << "c : " << c << "\n";
      std::cout << "Delta : " << delta << "\n";

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
      return out << "Sphere([" << sphere.origin.x() << ", " << sphere.origin.y() << ", "
                 << sphere.origin.z() << "], radius: " << sphere.radius << ")\n";
    }

  }  // namespace geometry

}  // namespace yart
