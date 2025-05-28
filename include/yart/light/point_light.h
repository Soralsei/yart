#pragma once

#include "yart/light/light.h"

namespace yart {

  namespace light {

    class PointLight : public Light {
    public:
      PointLight() = default;
      ~PointLight();

      PointLight(glm::vec3 _position, float _light_energy, float _light_specular,
                 color::Color _light_color);
      PointLight(glm::vec3 _position);
    };

  }  // namespace light

}  // namespace yart
