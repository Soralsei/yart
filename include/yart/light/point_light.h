#pragma once

#include "yart/light/light.h"

namespace yart {

  namespace light {

    class PointLight : public Light<PointLight> {
    public:
      PointLight() = default;
      ~PointLight();

      PointLight(Eigen::Vector3f _position, float _light_energy, float _light_specular,
                 color::Color _light_color);
      PointLight(Eigen::Vector3f _position);
    };

  }  // namespace light

}  // namespace yart
