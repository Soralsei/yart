#include "yart/light/light.hpp"

#include <glm/ext/vector_float4.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/norm.hpp>
#include <optional>

#include "yart/core/material.hpp"
#include "yart/core/ray.hpp"
#include "yart/core/world.hpp"
#include "yart/geometry/hit.hpp"
#include "yart/geometry/intersection.hpp"
#include "yart/geometry/shape.hpp"
#include "yart/util/math.hpp"

namespace yart {

  namespace light {

    Light::Light(glm::vec3 _position, float _light_energy, float _light_specular,
                 color::Color _light_color)
        : Parent(_position),
          light_energy(_light_energy),
          light_specular(_light_specular),
          light_color(_light_color) {}

    Light::Light(glm::vec3 _position) : Parent(_position) {}

    Light::Light() : Parent() {}

    float Light::get_energy() const { return light_energy; }

    float Light::get_specular() const { return light_specular; }

    const color::Color& Light::get_color() const { return light_color; }

    void Light::set_energy(float _light_energy) { light_energy = _light_energy; }

    void Light::set_specular(float _light_specular) { light_specular = _light_specular; }

    void Light::set_color(const color::Color& _light_color) { light_color = _light_color; }

    void Light::set_color(float r, float g, float b) { light_color = color::Color(r, g, b); }

    void Light::set_color(float r, float g, float b, float a) {
      light_color = color::Color(r, g, b, a);
    }

    bool Light::self_equal(const Light& other) const {
      return math::approx_equals(light_energy, other.light_energy)
             && math::approx_equals(light_specular, other.light_specular)
             && light_color == other.light_color;
    }

    color::Color phong_lighting(const Material& material, const Light& light,
                                const glm::vec4& point, const glm::vec4& eye,
                                const glm::vec4& normal, bool is_shadowed) {
      color::Color effective_color
          = material.get_diffuse_color() * (light.get_color() * light.get_energy());
      color::Color ambient = effective_color * material.get_ambient();
      if (is_shadowed) {
        return ambient;
      }
      glm::vec4 lightv = glm::normalize(glm::vec4{light.position(), 1} - point);
      float light_dot_normal = glm::dot(lightv, normal);

      color::Color specular = color::Black;
      color::Color diffuse = color::Black;

      if (light_dot_normal >= 0) {
        diffuse = effective_color * material.get_diffuse() * light_dot_normal;
        glm::vec4 reflectv = math::reflect(-lightv, normal);
        float reflect_dot_eye = glm::dot(reflectv, eye);

        if (reflect_dot_eye > 0) {
          float factor = std::pow(reflect_dot_eye, material.get_shininess());
          specular = light.get_color() * light.get_energy() * material.get_specular() * factor
                     * light.get_specular();
        }
      }

      return ambient + diffuse + specular;
    }

    color::Color shade_hit(const World& world, const geometry::Hit& hit) {
      color::Color shade;
      auto object = hit.get_object().lock();
      if (object == nullptr) return shade;

      auto material = object->get_material();
      glm::vec4 position = hit.get_position();
      glm::vec4 over_position = hit.get_over_position();
      glm::vec4 eye = hit.get_eye();
      glm::vec4 normal = hit.get_normal();

      for (auto&& light : world.get_light_sources()) {
        bool in_shadows = is_shadowed(world, *light, over_position);
        shade += phong_lighting(material, *light, position, eye, normal, in_shadows);
      }

      return shade;
    }

    bool is_shadowed(const World& world, const Light& light, const glm::vec4& point) {
      glm::vec4 lightv = glm::vec4{light.position(), 1} - point;
      float distance = glm::l2Norm(glm::vec3{lightv});
      glm::vec4 direction = lightv / distance;

      Ray r = {point, direction};
      auto intersections = world.intersections(r);
      std::optional<geometry::Intersection> hit = geometry::hit(intersections);

      return hit.has_value() && hit->get_t() < distance;
    }

  }  // namespace light

}  // namespace yart
