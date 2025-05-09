#include "yart/light/point_light.h"

namespace yart {

  namespace light {

    PointLight::~PointLight() {}

    PointLight::PointLight(Eigen::Vector3f _position, float _light_energy, float _light_specular,
                           color::Color _light_color)
        : Light(_position, _light_energy, _light_specular, _light_color) {}

    PointLight::PointLight(Eigen::Vector3f _position) : Light(_position) {}

  }  // namespace light

}  // namespace yart
