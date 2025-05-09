#pragma once
#include <iostream>
#include <memory>
#include <vector>

#include "Eigen/Dense"
#include "yart/geometry/defines.h"
#include "yart/geometry/intersection.h"

namespace yart {

  class Ray;
  class Material;

  namespace geometry {
    template <class ShapeType> class Intersection;
  }  // namespace geometry

  class Object3D : public std::enable_shared_from_this<Object3D> {
  protected:
    geometry::Transform3D transform;
    std::unique_ptr<Material> material;

  public:
    Object3D(Eigen::Vector3f _origin);
    Object3D(Eigen::Vector3f _origin, Eigen::Vector4f _rotation);
    Object3D(geometry::Transform3D _transform);
    Object3D();
    virtual ~Object3D() = default;

    virtual std::vector<geometry::Intersection<Object3D>> intersections(const yart::Ray& ray);

    const geometry::Transform3D& get_transform() const;
    void set_transform(const geometry::Transform3D& _transform);

    Eigen::Vector3f position() const;
    Eigen::Vector3f orientation() const;
    geometry::Quaternion quaternion() const;

    friend std::ostream& operator<<(std::ostream& out, const Object3D& shape);

    const Material& get_material() const;
    Object3D& set_material(const Material& _material);
  };

}  // namespace yart
