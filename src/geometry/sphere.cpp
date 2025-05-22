#include "yart/geometry/sphere.h"

#include <iostream>

#include "yart/core/object3d.h"
#include "yart/core/ray.h"
#include "yart/geometry/intersection.h"
#include "yart/geometry/shape.h"
#include "yart/util/math.h"
#include "yart/util/vector.h"

namespace yart {

  namespace geometry {

    Sphere::Sphere(Transform3D _transform, float _radius) : Parent(_transform), radius(_radius) {}

    Sphere::Sphere(Eigen::Vector3f _position, float _radius) : Parent(_position), radius(_radius) {}

    Sphere::Sphere(float _radius) : Parent(), radius(_radius) {}
    Sphere::Sphere(const Sphere& other) : Parent(other.transform), radius(other.radius) {}
    Sphere::Sphere() : Parent(), radius(1.0f) {}

    Sphere::~Sphere() {}

    std::vector<Intersection> Sphere::_intersections(const Ray& ray) {
      // Transform the ray to the local space of the shape
      Eigen::Vector3f self_to_ray = ray.get_origin() - position();
      auto direction = ray.get_direction();
      float a = direction.dot(direction);
      float b = 2 * direction.dot(self_to_ray);
      float c = self_to_ray.dot(self_to_ray) - radius * radius;

      float delta = b * b - 4 * a * c;

      // No intersections
      if (delta < 0) {
        return std::vector<Intersection>{};
      }
      auto this_ptr = shared_from_this();
      Intersection i1 = {this_ptr, (-b - std::sqrt(delta)) / (2 * a)};
      Intersection i2 = {this_ptr, (-b + std::sqrt(delta)) / (2 * a)};
      // Return 2 intersections whether ray is tangent or not
      return make_vec(i1, i2);
    }

    Eigen::Vector3f Sphere::normal_at(const Eigen::Vector3f& point) const {
      // Transform the point to the local space of the shape
      auto transformed_point = transform.inverse() * point;
      auto normal_object = (transformed_point).normalized();
      // Transform the normal back to the world space
      auto transform_world = transform.linear().inverse().transpose();
      return (transform_world * normal_object).normalized();
    }

    std::ostream& operator<<(std::ostream& out, const Sphere& sphere) {
      return out << "Sphere([" << sphere.position().x() << ", " << sphere.position().y() << ", "
                 << sphere.position().z() << "], radius: " << sphere.radius << ")";
    }

    bool Sphere::self_equal(const Sphere& other) const {
      std::cout << (*this) << '\n';
      return math::approx_equals(radius, other.radius);
    }

    std::string Sphere::as_string() const {
      std::stringstream repr;
      repr << "Sphere(\ntransform : " << transform.matrix() << ", radius : " << radius << ")";
      return repr.str();
    }

  }  // namespace geometry

}  // namespace yart
