#include "yart/geometry/hit.h"

#include "yart/core/object3d.h"
#include "yart/core/ray.h"
#include "yart/geometry/defines.h"
#include "yart/geometry/intersection.h"
#include "yart/geometry/shape.h"

namespace yart {

  namespace geometry {

    float Hit::get_t() const { return t; }

    std::weak_ptr<Shape3D> Hit::get_object() const { return object; }

    glm::vec4 Hit::get_position() const { return position; }
    glm::vec4 Hit::get_over_position() const { return over_position; }

    glm::vec4 Hit::get_eye() const { return eye; }

    glm::vec4 Hit::get_normal() const { return normal; }

    bool Hit::is_inside() const { return inside; }

    std::shared_ptr<Hit> Hit::precompute_hit(const Ray& ray, const Intersection& intersection) {
      auto hit = std::make_shared<Hit>();

      hit->object = intersection.get_object();
      hit->t = intersection.get_t();
      hit->position = ray.position(intersection.get_t());
      hit->eye = -ray.get_direction();

      glm::vec4 normal = hit->object.lock()->normal_at(hit->position);

      bool is_inside = glm::dot(normal, hit->eye) < 0;
      hit->inside = is_inside;

      float direction = is_inside ? -1 : 1;
      hit->normal = direction * normal;
      hit->over_position = hit->position + hit->normal * static_cast<float>(SHADOW_EPSILON);

      return hit;
    }

  }  // namespace geometry

}  // namespace yart
