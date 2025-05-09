#include "yart/light/light.h"

#include "yart/core/material.h"
#include "yart/core/object3d.h"

namespace yart {

  namespace light {

    Light::Light(Eigen::Vector3f _position, float _light_energy, float _light_specular,
                 color::Color _light_color)
        : Object3D::Object3D(_position),
          light_energy(_light_energy),
          light_specular(_light_specular),
          light_color(_light_color) {}

    Light::Light(Eigen::Vector3f _position) : Object3D::Object3D(_position) {}

    Light::Light() : Object3D::Object3D() {}

    float Light::get_energy() const { return light_energy; }

    float Light::get_specular() const { return light_specular; }

    const color::Color& Light::get_light_color() const { return light_color; }

    void Light::set_energy(float _light_energy) { light_energy = _light_energy; }

    void Light::set_specular(float _light_specular) { light_specular = _light_specular; }

    void Light::set_color(const color::Color& _light_color) { light_color = _light_color; }

    void Light::set_color(float r, float g, float b) { light_color = color::Color(r, g, b); }

    void Light::set_light_color(float r, float g, float b, float a) {
      light_color = color::Color(r, g, b, a);
    }

    color::Color phong_lighting(const Material& material, const Light& light,
                                const Eigen::Vector3f& point, const Eigen::Vector3f& eye,
                                const Eigen::Vector3f& normal) {
      color::Color effective_color
          = material.get_diffuse_color() * (light.get_light_color() * light.get_energy());
      Eigen::Vector3f lightv = (light.position() - point).normalized();
      color::Color ambient = effective_color * material.get_ambient();
      float light_dot_normal = lightv.dot(normal);

      color::Color specular = color::Black;
      color::Color diffuse = color::Black;

      if (light_dot_normal >= 0) {
        diffuse = effective_color * material.get_diffuse() * light_dot_normal;
        Eigen::Vector3f reflectv = math::reflect(-lightv, normal);
        float reflect_dot_eye = reflectv.dot(eye);

        if (reflect_dot_eye > 0) {
          float factor = std::pow(reflect_dot_eye, material.get_shininess());
          specular
              = (light.get_light_color() * light.get_energy()) * material.get_specular() * factor;
        }
      }

      return ambient + diffuse + specular;
    }

  }  // namespace light

}  // namespace yart
