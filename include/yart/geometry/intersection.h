#pragma once
#include <memory>

namespace yart {
  namespace geometry {
    template <class ShapeType> class Intersection {
    private:
      float t;
      std::weak_ptr<ShapeType> object;

    public:
      Intersection(std::weak_ptr<ShapeType> obj, float _t) : object(obj), t(_t) {}
      ~Intersection() {}

      std::weak_ptr<ShapeType> get_object() { return object; }

      float get_t() { return t; }
    };
  }  // namespace geometry
}  // namespace yart
