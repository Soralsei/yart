#include "yart/geometry/shape.h"

#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/io.hpp>
#include <glm/matrix.hpp>
#include <iostream>

#include "yart/core/material.h"
#include "yart/core/ray.h"
#include "yart/geometry/intersection.h"

namespace yart {
  namespace geometry {

    Shape3D::Shape3D(glm::vec3 _origin) : Parent(_origin) {
      material = std::make_shared<Material>();
    }

    Shape3D::Shape3D(glm::vec3 _origin, glm::vec4 _rotation) : Parent(_origin, _rotation) {
      material = std::make_shared<Material>();
    }

    Shape3D::Shape3D(Transform _transform) : Parent(_transform) {
      material = std::make_shared<Material>();
    }

    Shape3D::Shape3D() : Parent() { material = std::make_shared<Material>(); }

    Shape3D::~Shape3D() {}

    std::vector<Intersection> Shape3D::intersections(const Ray& ray) {
      // std::cout << "Self : " << *this << "\n";
      glm::mat4 inverse_transform = glm::inverse(transform.matrix());
      Ray transformed_ray = ray.transform(inverse_transform);
      // std::cout << "Ray : " << ray << "\n";
      // std::cout << "Local space ray : " << transformed_ray << "\n";
      return local_intersections(transformed_ray);
    }

    glm::vec4 Shape3D::normal_at(const glm::vec4& point) {
      glm::mat4 inverse_transform = glm::inverse(transform.matrix());
      glm::vec4 local_point = inverse_transform * point;
      glm::vec4 local_normal = local_normal_at(local_point);

      glm::mat3 T = glm::transpose(glm::mat3{inverse_transform});
      glm::vec3 world_normal = T * glm::vec3{local_normal};

      auto normal = glm::normalize(glm::vec4{world_normal, 0.0f});

      // std::cout << "Inverse transform: " << inverse_transform << "\n";
      // std::cout << "World point: " << point << "\n";
      // std::cout << "Object point: " << local_point << "\n";
      // std::cout << "Local normal: " << local_normal << "\n";
      // std::cout << "World normal: " << normal << "\n";

      return normal;
    }

    Material& Shape3D::get_material() { return (*material); }
    void Shape3D::set_material(const Material& mat) { *material = mat; }
    void Shape3D::set_material(std::shared_ptr<Material> mat) { material = mat; }

    bool Shape3D::self_equal(const Shape3D& other) const {
      return (*material) == (*other.material);
    }

    std::ostream& operator<<(std::ostream& out, Shape3D& shape) { return out << shape.as_string(); }
  }  // namespace geometry

}  // namespace yart
