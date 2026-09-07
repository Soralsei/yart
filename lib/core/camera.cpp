#include "yart/core/camera.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/matrix.hpp>

#include "yart/core/ray.hpp"
#include "yart/geometry/transform.hpp"

namespace yart {

  Camera::Camera(int _hsize, int _vsize, float _fov)
      : Object3D::Object3D(), hsize(_hsize), vsize(_vsize), fov(_fov) {
    float half_view = std::tan(fov / 2);
    float aspect_ratio = static_cast<float>(hsize) / static_cast<float>(vsize);

    if (aspect_ratio >= 1) {
      half_width = half_view;
      half_height = half_view / aspect_ratio;
    } else {
      half_width = half_view * aspect_ratio;
      half_height = half_view;
    }

    pixel_size = (half_width * 2) / static_cast<float>(hsize);
  }

  int Camera::get_hsize() const { return hsize; }
  int Camera::get_vsize() const { return vsize; }
  float Camera::get_fov() const { return fov; }
  float Camera::get_pixel_size() const { return pixel_size; }

  Ray Camera::ray_to(int x, int y) {
    // Offset from edge of pixel (index passed as x and y) and center of pixel
    float x_offset = (static_cast<float>(x) + 0.5f) * pixel_size;
    float y_offset = (static_cast<float>(y) + 0.5f) * pixel_size;

    float world_x = half_width - x_offset;
    float world_y = half_height - y_offset;

    glm::mat4 inverse = glm::inverse(transform.matrix());
    glm::vec4 pixel = inverse * glm::vec4{world_x, world_y, -1.0f, 1.0f};
    glm::vec4 origin = inverse * glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};

    glm::vec4 direction = glm::normalize(pixel - origin);

    return Ray{origin, direction};
  }

  void Camera::look_at(const glm::vec3& target, const glm::vec3& up) {
    transform = Camera::get_view_transform(position(), target, up);
  }

  glm::mat4 Camera::get_view_transform(const glm::vec3& from, const glm::vec3& to,
                                       const glm::vec3& up) {
    return glm::lookAt(from, to, up);
  }

}  // namespace yart
