#pragma once

#include "yart/geometry/defines.h"
#include "yart/geometry/intersection.h"
#include "yart/geometry/shape.h"

namespace yart {

  namespace geometry {

    class Plane : public comparable<Plane, Object3D, Shape3D> {
      using Parent = comparable<Plane, Object3D, Shape3D>;

    private:
      virtual std::vector<Intersection> local_intersections(const Ray& ray) override;
      virtual Eigen::Vector4f local_normal_at(const Eigen::Vector4f& point) const override;
      bool m_infinite = true;
      float m_width = 1;
      float m_length = 1;

    protected:
      virtual bool self_equal(const Plane& other) const override;

    public:
      // Assumes unit plane if is_infinite is false
      Plane(Transform3D _transform, bool is_infinite);
      // Assumes unit plane if is_infinite is false
      Plane(Eigen::Vector3f _origin, bool is_infinite);
      // Assumes unit plane if is_infinite is false
      Plane(bool is_infinite);

      // Assumes plane is not infinite
      Plane(Transform3D _transform, float width, float length);
      Plane(Eigen::Vector3f _origin, float width, float length);
      Plane(float width, float length);
      Plane();

      // Copy constructor
      Plane(const Plane& other);

      ~Plane();

      std::string as_string() const override;

      friend std::ostream& operator<<(std::ostream& out, const Plane& sphere);
    };

  }  // namespace geometry

}  // namespace yart
