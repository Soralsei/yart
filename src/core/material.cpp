#include "yart/core/material.h"

#include "yart/util/math.h"

namespace yart {
  Material::~Material() {}

  float Material::get_ambient() const { return ambient; }
  float Material::get_diffuse() const { return diffuse; }
  float Material::get_specular() const { return specular; }
  float Material::get_shininess() const { return shininess; }
  color::Color Material::get_diffuse_color() const { return diffuse_color; }

  Material& Material::set_ambient(float _ambient) {
    ambient = _ambient;
    return (*this);
  }
  Material& Material::set_diffuse(float _diffuse) {
    diffuse = _diffuse;
    return (*this);
  }
  Material& Material::set_specular(float _specular) {
    specular = _specular;
    return (*this);
  }
  Material& Material::set_shininess(float _shininess) {
    shininess = _shininess;
    return (*this);
  }
  Material& Material::set_diffuse_color(const color::Color& _diffuse_color) {
    diffuse_color = _diffuse_color;
    return (*this);
  }
  Material& Material::set_diffuse_color(float r, float g, float b) {
    diffuse_color = color::Color(r, g, b);
    return (*this);
  }
  Material& Material::set_diffuse_color(float r, float g, float b, float a) {
    diffuse_color = color::Color(r, g, b, a);
    return (*this);
  }

  bool operator==(const Material& lhs, const Material& rhs) {
    return math::approx_equals(lhs.diffuse, rhs.diffuse)
           && math::approx_equals(lhs.ambient, rhs.ambient)
           && math::approx_equals(lhs.specular, rhs.specular)
           && math::approx_equals(lhs.shininess, rhs.shininess)
           && lhs.diffuse_color == rhs.diffuse_color;
  }

}  // namespace yart
