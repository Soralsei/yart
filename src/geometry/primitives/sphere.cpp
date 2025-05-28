#include "yart/geometry/primitives/sphere.h"

#include <glm/gtx/io.hpp>
#include <iostream>

#include "yart/core/object3d.h"
#include "yart/core/ray.h"
#include "yart/geometry/intersection.h"
#include "yart/geometry/shape.h"
#include "yart/util/math.h"
#include "yart/util/vector.h"

namespace yart {

  namespace geometry {

    Sphere::Sphere(Transform _transform, float _radius) : Parent(_transform), radius(_radius) {}

    Sphere::Sphere(glm::vec3 _position, float _radius) : Parent(_position), radius(_radius) {}

    Sphere::Sphere(float _radius) : Parent(), radius(_radius) {}
    Sphere::Sphere(const Sphere& other) : Parent(other.transform), radius(other.radius) {}
    Sphere::Sphere() : Parent(), radius(1.0f) {}

    Sphere::~Sphere() {}

    std::vector<Intersection> Sphere::local_intersections(const Ray& ray) {
      // Ray should already be in local frame of the sphere
      // So we can use the ray origin and direction directly
      glm::vec4 self_to_ray = ray.get_origin() - glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};
      auto direction = ray.get_direction();
      float a = glm::dot(direction, direction);
      float b = 2 * glm::dot(direction, self_to_ray);
      float c = glm::dot(self_to_ray, self_to_ray) - radius * radius;

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

    glm::vec4 Sphere::local_normal_at(const glm::vec4& local_point) const {
      return glm::normalize(local_point - glm::vec4{0.0f, 0.0f, 0.0f, 1.0f});
    }

    std::ostream& operator<<(std::ostream& out, const Sphere& sphere) {
      return out << "Sphere([" << sphere.position() << "], radius: " << sphere.radius << ")";
    }

    bool Sphere::self_equal(const Sphere& other) const {
      std::cout << (*this) << '\n';
      return math::approx_equals(radius, other.radius);
    }

    std::string Sphere::as_string() {
      std::stringstream repr;
      repr << "Sphere(\ntransform : \n[" << transform.matrix() << " ], radius : " << radius
           << "\n)";
      return repr.str();
    }

  }  // namespace geometry

}  // namespace yart
