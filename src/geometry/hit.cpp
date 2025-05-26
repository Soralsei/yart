#include "yart/geometry/hit.h"

#include <iostream>

#include "yart/core/object3d.h"
#include "yart/core/ray.h"
#include "yart/geometry/intersection.h"
#include "yart/geometry/shape.h"

namespace yart {

  namespace geometry {

    float Hit::get_t() const { return t; }

    std::weak_ptr<Shape3D> Hit::get_object() const { return object; }

    Eigen::Vector4f Hit::get_position() const { return position; }

    Eigen::Vector4f Hit::get_eye() const { return eye; }

    Eigen::Vector4f Hit::get_normal() const { return normal; }

    bool Hit::is_inside() const { return inside; }

    std::shared_ptr<Hit> Hit::precompute_hit(const Ray& ray,
                                             const Intersection& intersection) {
      auto hit = std::make_shared<Hit>();

      hit->object = intersection.get_object();
      hit->t = intersection.get_t();
      hit->position = ray.position(intersection.get_t());
      hit->eye = -ray.get_direction();

      Eigen::Vector4f normal = hit->object.lock()->normal_at(hit->position);

      bool is_inside = normal.dot(hit->eye) < 0;
      hit->inside = is_inside;

      int direction = is_inside ? -1 : 1;
      hit->normal = direction * normal;

      return hit;
    }

  }  // namespace geometry

}  // namespace yart
