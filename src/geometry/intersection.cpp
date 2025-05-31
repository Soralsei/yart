#include "yart/geometry/intersection.hpp"

#include <limits>

#include "yart/geometry/shape.hpp"

namespace yart {
  namespace geometry {
    Intersection::Intersection(std::weak_ptr<Shape3D> obj, float _t) : t(_t), object(obj) {}
    Intersection::~Intersection() {}

    std::weak_ptr<Shape3D> Intersection::get_object() const { return object; }

    float Intersection::get_t() const { return t; }

    bool operator==(const Intersection& lhs, const Intersection& rhs) {
      return lhs.get_t() == rhs.get_t() && lhs.get_object().lock() == rhs.get_object().lock();
    }

    std::ostream& operator<<(std::ostream& out, const Intersection& intersection) {
      return out << "Intersection(t: " << intersection.get_t()
                 << ", object: " << *(intersection.get_object().lock()) << ")";
    }

    Intersection* hit(std::vector<Intersection>& intersections) {
      float min_t = std::numeric_limits<float>::max();
      Intersection* min_intersection = nullptr;
      for (auto&& i : intersections) {
        if (i.get_t() >= 0 && i.get_t() < min_t) {
          min_t = i.get_t();
          min_intersection = &i;
        }
      }

      return min_intersection;
    }
  }  // namespace geometry
}  // namespace yart
