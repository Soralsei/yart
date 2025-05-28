#include "yart/geometry/primitives/plane.h"

#include <glm/gtx/io.hpp>
#include <iostream>
#include <sstream>
#include <vector>

#include "yart/core/object3d.h"
#include "yart/core/ray.h"
#include "yart/geometry/defines.h"
#include "yart/geometry/intersection.h"
#include "yart/geometry/shape.h"
#include "yart/util/math.h"

namespace yart {

  namespace geometry {

    Plane::Plane(Transform _transform, bool is_infinite)
        : Parent(_transform), m_infinite(is_infinite) {}

    Plane::Plane(glm::vec3 _position, bool is_infinite)
        : Parent(_position), m_infinite(is_infinite) {}

    Plane::Plane(bool is_infinite) : Parent(), m_infinite(is_infinite) {}

    Plane::Plane() : Parent(), m_infinite(true) {}

    Plane::Plane(Transform _transform, float width, float length)
        : Parent(_transform), m_infinite(false), m_width(width), m_length(length) {}

    Plane::Plane(glm::vec3 _origin, float width, float length)
        : Parent(_origin), m_infinite(false), m_width(width), m_length(length) {}

    Plane::Plane(float width, float length) : m_infinite(false), m_width(width), m_length(length) {}

    Plane::Plane(const Plane& other) : Parent(other.transform), m_infinite(other.m_infinite) {}

    Plane::~Plane() {}

    std::vector<Intersection> Plane::local_intersections(const Ray& ray) {
      // If the ray does not have a Y component to its direction
      // it will never hit an XZ plane
      if (static_cast<double>(std::abs(ray.get_direction().y)) < EPSILON / 10) {
        return std::vector<Intersection>{};
      }
      float t = -ray.get_origin().y / ray.get_direction().y;
      std::vector<Intersection> i;
      auto shared_this = shared_from_this();

      // If the plane is infinite, just check when the ray hits it
      // else, check if the point lies within the plane's width and
      // length
      if (m_infinite) {
        i.push_back(Intersection{shared_this, t});
      } else {
        glm::vec4 point = ray.position(t);
        if (std::abs(point.x) < m_width / 2 && std::abs(point.z) < m_length / 2) {
          i.push_back(Intersection{shared_this, t});
        }
      }
      return i;
    }

    glm::vec4 Plane::local_normal_at(const glm::vec4& _) const {
      return glm::vec4{0.0f, 1.0f, 0.0f, 0.0f};  // Normal is always (0, 1, 0)
    }

    std::ostream& operator<<(std::ostream& out, Plane& plane) { return out << plane.as_string(); }

    bool Plane::self_equal(const Plane& other) const {
      return m_infinite == other.m_infinite
             || (math::approx_equals(m_width, other.m_width)
                 && math::approx_equals(m_length, other.m_length));
    }

    std::string Plane::as_string() {
      std::stringstream repr;
      repr << "Plane(\nposition : \n[" << position() << " ], orientation: " << orientation()
           << ", is infinite : " << m_infinite << ", width :" << m_width << ", length: " << m_length
           << ")";
      return repr.str();
    }

  }  // namespace geometry

}  // namespace yart
