#include "yart/geometry/shape.h"

#include "yart/core/material.h"
#include "yart/core/ray.h"
#include "yart/geometry/intersection.h"

namespace yart {
  namespace geometry {

    Shape3D::Shape3D(Eigen::Vector3f _origin) : Parent(_origin) {
      material = std::make_shared<Material>();
    }

    Shape3D::Shape3D(Eigen::Vector3f _origin, Eigen::Vector4f _rotation)
        : Parent(_origin, _rotation) {
      material = std::make_shared<Material>();
    }

    Shape3D::Shape3D(Transform3D _transform) : Parent(_transform) {
      material = std::make_shared<Material>();
    }

    Shape3D::Shape3D() : Parent() { material = std::make_shared<Material>(); }

    Shape3D::~Shape3D() {}

    std::vector<Intersection> Shape3D::intersections(const Ray& ray) {
      // std::cout << "Self : " << *this << "\n";
      Ray transformed_ray = ray.transform(transform.inverse());
      // std::cout << "Ray : " << ray << "\n";
      // std::cout << "Local space ray : " << transformed_ray << "\n";
      return local_intersections(transformed_ray);
    }

    Eigen::Vector4f Shape3D::normal_at(const Eigen::Vector4f& point) {
      Eigen::Vector4f local_point = transform.inverse() * point;
      Eigen::Vector4f local_normal = local_normal_at(local_point);
      Eigen::Vector4f world_normal = Eigen::Vector4f::Zero();
      world_normal.head<3>() = transform.linear().inverse().transpose() * local_normal.head<3>();

      return world_normal.normalized();
    }

    Material& Shape3D::get_material() { return (*material); }
    void Shape3D::set_material(const Material& mat) { *material = mat; }
    void Shape3D::set_material(std::shared_ptr<Material> mat) { material = mat; }

    bool Shape3D::self_equal(const Shape3D& other) const {
      return (*material) == (*other.material);
    }

    std::ostream& operator<<(std::ostream& out, const Shape3D& shape) {
      return out << shape.as_string();
    }
  }  // namespace geometry

}  // namespace yart
