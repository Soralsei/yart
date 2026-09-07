#include "yart/light/point_light.hpp"

namespace yart {

  namespace light {

    PointLight::~PointLight() {}

    PointLight::PointLight(glm::vec3 _position, float _light_energy, float _light_specular,
                           color::Color _light_color)
        : Light(_position, _light_energy, _light_specular, _light_color) {}

    PointLight::PointLight(glm::vec3 _position) : Light(_position) {}

  }  // namespace light

}  // namespace yart
