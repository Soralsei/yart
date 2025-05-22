#pragma once

#include <memory>

#include "Eigen/Dense"
#include "yart/core/object3d.h"
#include "yart/geometry/defines.h"
#include "yart/traits/comparable.h"
#include "yart/traits/shared_from_this.h"

namespace yart {

  class Ray;
  class Material;

  namespace geometry {
    using namespace traits;

    class Intersection;

    class Shape3D : public enable_shared_from_this<comparable<Shape3D, Object3D>, Shape3D> {
      using Parent = enable_shared_from_this<comparable<Shape3D, Object3D>, Shape3D>;

    protected:
      bool self_equal(const Shape3D& other) const override;
      std::shared_ptr<Material> material;

    private:
      virtual std::vector<Intersection> _intersections(const Ray& ray) = 0;
      virtual std::string as_string() const = 0;

    public:
      Shape3D(Eigen::Vector3f _origin);

      Shape3D(Eigen::Vector3f _origin, Eigen::Vector4f _rotation);

      Shape3D(Transform3D _transform);
      Shape3D();
      ~Shape3D();

      std::vector<geometry::Intersection> intersections(const Ray& ray);
      virtual Eigen::Vector3f normal_at(const Eigen::Vector3f& point) const = 0;

      Material& get_material();
      void set_material(const Material& mat);

      friend std::ostream& operator<<(std::ostream& out, const Shape3D&);
    };

  }  // namespace geometry

}  // namespace yart
