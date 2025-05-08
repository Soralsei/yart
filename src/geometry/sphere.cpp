#include <iostream>

#include "yart/geometry/sphere.h"

#include "yart/geometry/intersection.h"
#include "yart/core/ray.h"
#include "yart/util/vector.h"

namespace yart {

  namespace geometry {

    Sphere::Sphere(Transform3d _transform, float _radius)
        : Shape3D<Sphere>::Shape3D(_transform), radius(_radius) {}

    Sphere::Sphere(Eigen::Vector3f _position, float _radius)
        : Shape3D<Sphere>::Shape3D(_position), radius(_radius) {}

    Sphere::Sphere(float _radius) : Shape3D<Sphere>::Shape3D(), radius(_radius) {}
    Sphere::Sphere(const Sphere& other)
        : Shape3D<Sphere>::Shape3D(other.transform), radius(other.radius) {}
    Sphere::Sphere() : Shape3D<Sphere>::Shape3D(), radius(1.0f) {}

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

    Eigen::Vector3f Sphere::normal_at(const Eigen::Vector3f& point) {
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

  }  // namespace geometry

}  // namespace yart
