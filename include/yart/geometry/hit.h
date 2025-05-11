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

      Eigen::Vector3f position;
      Eigen::Vector3f eye;
      Eigen::Vector3f normal;

      bool inside = false;

    public:
      Hit() = default;
      ~Hit() = default;

      float get_t() const;
      std::weak_ptr<Shape3D> get_object() const;
      Eigen::Vector3f get_position() const;
      Eigen::Vector3f get_eye() const;
      Eigen::Vector3f get_normal() const;

      bool is_inside() const;

      static std::shared_ptr<Hit> precompute_hit(const Ray& ray, const Intersection& intersection);
    };

  }  // namespace geometry

}  // namespace yart
