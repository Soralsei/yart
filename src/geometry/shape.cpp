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
      Ray transformed_ray = ray * transform.inverse();
      return _intersections(transformed_ray);
    }

    Material& Shape3D::get_material() { return (*material); }
    void Shape3D::set_material(const Material& mat) { *material = mat; }

    bool Shape3D::self_equal(const Shape3D& other) const {
      return (*material) == (*other.material);
    }

    std::ostream& operator<<(std::ostream& out, const Shape3D& shape) {
      return out << shape.as_string();
    }
  }  // namespace geometry

}  // namespace yart
