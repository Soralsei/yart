#pragma once
#include <memory>
#include <limits>
#include <vector>

namespace yart {
  namespace geometry {
    template <class ShapeType> class Intersection {
    private:
      float t;
      std::weak_ptr<ShapeType> object;

    public:
      Intersection(std::weak_ptr<ShapeType> obj, float _t) : object(obj), t(_t) {}
      ~Intersection() {}

      std::weak_ptr<ShapeType> get_object() const { return object; }

      inline float get_t() const { return t; }

      friend bool operator==(const Intersection<ShapeType>& lhs, const Intersection<ShapeType>& rhs) {
        return lhs.get_t() == rhs.get_t() && lhs.get_object().lock() == rhs.get_object().lock();
      }
      
      template <class T>
      friend std::ostream& operator<<(std::ostream& out, const Intersection<T>& intersection);
    };

    template <class ShapeType> std::ostream& operator<<(std::ostream& out, const Intersection<ShapeType>& intersection) {
      return out << "Intersection(t: " << intersection.get_t() << ", object: " << *(intersection.get_object().lock()) << ")";
    }

    template <class ShapeType> 
    Intersection<ShapeType>* hit(std::vector<Intersection<ShapeType>>& intersections) {
      float min_t = std::numeric_limits<float>::max();
      Intersection<ShapeType> *min_intersection = nullptr;
      for (auto &&i : intersections)
      {
        if (i.get_t() >= 0 && i.get_t() < min_t)
        {
          min_t = i.get_t();
          min_intersection = &i;
        }
      }
      
      return min_intersection;
    }
  }  // namespace geometry
}  // namespace yart
