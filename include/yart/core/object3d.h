#pragma once
#include <iostream>
#include <memory>

#include "Eigen/Dense"
#include "yart/geometry/defines.h"
#include "yart/traits/comparable.h"

namespace yart {

  using namespace traits;

  class Ray;

  class Object3D : public std::enable_shared_from_this<Object3D>, public comparable_base<Object3D> {
  private:
    inline static uint32_t global_id = 0;

  protected:
    virtual bool is_equal(const Object3D& rhs) const override;
    virtual bool self_equal(const Object3D& other) const override;

    uint32_t object_id;

  public:
    Object3D(Eigen::Vector3f _origin);
    Object3D(Eigen::Vector3f _origin, Eigen::Vector4f _rotation);
    Object3D(geometry::Transform3D _transform);
    Object3D();

    // Copy constructor
    Object3D(const Object3D& other) = default;
    Object3D(Object3D& other) = default;

    virtual ~Object3D();

    Eigen::Vector3f position() const;
    Eigen::Vector3f orientation() const;
    geometry::Quaternion quaternion() const;

    friend std::ostream& operator<<(std::ostream& out, const Object3D& shape);

    friend bool operator==(const Object3D& lhs, const Object3D& rhs);

    geometry::Transform3D transform;
  };

}  // namespace yart
