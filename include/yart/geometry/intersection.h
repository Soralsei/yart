#pragma once

#include <iostream>
#include <limits>
#include <memory>
#include <vector>

namespace yart {
  namespace geometry {
    class Shape3D;

    class Intersection {
    private:
      float t;
      std::weak_ptr<Shape3D> object;

    public:
      Intersection(std::weak_ptr<Shape3D> obj, float _t);
      ~Intersection();

      std::weak_ptr<Shape3D> get_object() const;

      float get_t() const;

      friend bool operator==(const Intersection& lhs, const Intersection& rhs);

      friend std::ostream& operator<<(std::ostream& out, const Intersection& intersection);
    };

    std::ostream& operator<<(std::ostream& out, const Intersection& intersection);

    Intersection* hit(std::vector<Intersection>& intersections);
  }  // namespace geometry
}  // namespace yart
