#pragma once
#include <memory>

#include "Eigen/Dense"

namespace yart {

  class Object3D;
  class Ray;

  namespace geometry {

    class Intersection;
    class Shape3D;

    class Hit {
    private:
      std::weak_ptr<Shape3D> object;
      float t;

      Eigen::Vector4f position;
      Eigen::Vector4f over_position;
      Eigen::Vector4f eye;
      Eigen::Vector4f normal;

      bool inside = false;

    public:
      Hit() = default;
      ~Hit() = default;

      float get_t() const;
      std::weak_ptr<Shape3D> get_object() const;
      Eigen::Vector4f get_position() const;
      Eigen::Vector4f get_over_position() const;
      Eigen::Vector4f get_eye() const;
      Eigen::Vector4f get_normal() const;

      bool is_inside() const;

      static std::shared_ptr<Hit> precompute_hit(const Ray& ray, const Intersection& intersection);
    };

  }  // namespace geometry

}  // namespace yart
