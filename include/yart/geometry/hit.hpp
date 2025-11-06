#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float4.hpp>
#include <memory>

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

      glm::vec4 position;
      glm::vec4 over_position;
      glm::vec4 eye;
      glm::vec4 normal;

      bool inside = false;

    public:
      Hit() = default;
      ~Hit() = default;

      float get_t() const;
      std::weak_ptr<Shape3D> get_object() const;
      glm::vec4 get_position() const;
      glm::vec4 get_over_position() const;
      glm::vec4 get_eye() const;
      glm::vec4 get_normal() const;

      bool is_inside() const;

      static Hit precompute_hit(const Ray& ray, const Intersection& intersection);
    };

  }  // namespace geometry

}  // namespace yart
