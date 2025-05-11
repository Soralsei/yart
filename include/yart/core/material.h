#pragma once
#include <cstdint>

#include "yart/image/color.h"

namespace yart { 

  class Material {
  private:
    color::Color diffuse_color = color::White;

    float ambient = 0.1f;
    float diffuse = 0.9f;
    float specular = 0.9f;
    float shininess = 200.0f;

  public:
    Material(const color::Color& _diffuse_color, float _ambient, float _diffuse, float _specular,
             float _shininess);
    Material(const color::Color& _diffuse_color, float _ambient, float _diffuse, float _specular);
    Material(const color::Color& _diffuse_color, float _ambient, float _diffuse);
    Material(const color::Color& _diffuse_color, float _ambient);
    Material(const color::Color& _diffuse_color);
    Material() = default;
    ~Material();

    float get_ambient() const;
    float get_diffuse() const;
    float get_specular() const;
    float get_shininess() const;
    color::Color get_diffuse_color() const;

    Material& set_ambient(float _ambient);
    Material& set_diffuse(float _diffuse);
    Material& set_specular(float _specular);
    Material& set_shininess(float _shininess);
    Material& set_diffuse_color(const color::Color& _diffuse_color);
    Material& set_diffuse_color(float r, float g, float b);
    Material& set_diffuse_color(float r, float g, float b, float a);

    friend bool operator==(const Material& lhs, const Material& rhs);
  };
}  // namespace yart
