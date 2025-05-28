#pragma once

#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>

#include "yart/core/object3d.h"
#include "yart/image/color.h"
#include "yart/traits/comparable.h"

namespace yart {

  using namespace traits;

  class Material;
  class World;

  namespace geometry {
    class Hit;
  }  // namespace geometry

  namespace light {

    class Light : public comparable<Light, Object3D> {
      using Parent = comparable<Light, Object3D>;

    protected:
      virtual bool self_equal(const Light& other) const override;

      float light_energy = 1.0f;
      float light_specular = 1.0f;
      color::Color light_color = color::White;

    public:
      Light();

      Light(glm::vec3 _position, float _light_energy, float _light_specular,
            color::Color _light_color);

      Light(glm::vec3 _position);

      ~Light() = default;

      float get_energy() const;
      float get_specular() const;
      const color::Color& get_color() const;
      void set_energy(float _light_energy);
      void set_specular(float _light_specular);
      void set_color(const color::Color& _light_color);
      void set_color(float r, float g, float b);
      void set_color(float r, float g, float b, float a);
    };

    color::Color phong_lighting(const Material& material, const Light& light,
                                const glm::vec4& point, const glm::vec4& eye,
                                const glm::vec4& normal, bool is_shadowed = false);

    color::Color shade_hit(const World& world, const geometry::Hit& hit);
    bool is_shadowed(const World& world, const Light& light, const glm::vec4& point);

  }  // namespace light

}  // namespace yart
