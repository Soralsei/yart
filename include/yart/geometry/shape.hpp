#pragma once

#include <glm/ext/vector_float4.hpp>
#include <memory>
#include <vector>

#include "yart/core/object3d.hpp"
#include "yart/geometry/defines.hpp"
#include "yart/traits/comparable.hpp"
#include "yart/traits/shared_from_this.hpp"

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
      virtual std::vector<Intersection> local_intersections(const Ray& ray) = 0;
      virtual glm::vec4 local_normal_at(const glm::vec4& local_point) const = 0;
      virtual std::string as_string() = 0;

    public:
      Shape3D(glm::vec3 _origin);

      Shape3D(glm::vec3 _origin, glm::vec4 _rotation);

      Shape3D(Transform _transform);
      Shape3D();
      ~Shape3D();

      std::vector<geometry::Intersection> intersections(const Ray& ray);
      glm::vec4 normal_at(const glm::vec4& point);

      Material& get_material();
      void set_material(const Material& mat);
      void set_material(std::shared_ptr<Material> mat);

      friend std::ostream& operator<<(std::ostream& out, Shape3D&);
    };

  }  // namespace geometry

}  // namespace yart
