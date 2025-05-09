#pragma once
#include <iostream>

#include "yart/core/material.h"
#include "yart/core/object3d.h"
#include "yart/geometry/defines.h"
#include "yart/image/color.h"
#include "yart/math/math.h"

namespace yart {

  namespace light {

    class Light : public Object3D {
    protected:
      float light_energy = 1.0f;
      float light_specular = 1.0f;
      color::Color light_color = color::White;

    public:
      Light();

      Light(Eigen::Vector3f _position, float _light_energy, float _light_specular,
            color::Color _light_color);

      Light(Eigen::Vector3f _position);

      ~Light() = default;

      float get_energy() const;
      float get_specular() const;
      const color::Color& get_light_color() const;
      void set_energy(float _light_energy);
      void set_specular(float _light_specular);
      void set_color(const color::Color& _light_color);
      void set_color(float r, float g, float b);
      void set_light_color(float r, float g, float b, float a);
    };

    color::Color phong_lighting(const Material& material, const Light& light,
                                const Eigen::Vector3f& point, const Eigen::Vector3f& eye,
                                const Eigen::Vector3f& normal);

  }  // namespace light

}  // namespace yart
