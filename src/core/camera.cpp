#include "yart/core/camera.h"

#include "yart/core/ray.h"
#include "yart/geometry/transform.h"

namespace yart {

  Camera::Camera(float _hsize, float _vsize, float _fov)
      : Object3D::Object3D(), hsize(_hsize), vsize(_vsize), fov(_fov) {
    float half_view = std::tan(fov / 2);
    float aspect_ratio = hsize / vsize;

    if (aspect_ratio >= 1) {
      half_width = half_view;
      half_height = half_view / aspect_ratio;
    } else {
      half_width = half_view * aspect_ratio;
      half_height = half_view;
    }

    pixel_size = (half_width * 2) / hsize;
  }

  uint32_t Camera::get_hsize() const { return hsize; }
  uint32_t Camera::get_vsize() const { return vsize; }
  float Camera::get_fov() const { return fov; }
  float Camera::get_pixel_size() const { return pixel_size; }

  Ray Camera::ray_to(int x, int y) const {
    // Offset from edge of pixel (index passed as x and y) and center of pixel
    float x_offset = (x + 0.5) * pixel_size;
    float y_offset = (y + 0.5) * pixel_size;

    float world_x = half_width - x_offset;
    float world_y = half_height - y_offset;

    auto pixel = transform.inverse() * Eigen::Vector3f{world_x, world_y, -1};
    auto origin = transform.inverse() * Eigen::Vector3f::Zero();

    auto direction = (pixel - origin).normalized();

    return Ray{origin, direction};
  }

  void Camera::look_at(const Eigen::Vector3f& target, const Eigen::Vector3f& up) {
    transform = Camera::get_view_transform(position(), target, up);
  }

  geometry::Transform3D Camera::get_view_transform(const Eigen::Vector3f& from,
                                                   const Eigen::Vector3f& to,
                                                   const Eigen::Vector3f& up) {
    geometry::Transform3D view_matrix = geometry::Transform3D::Identity();

    auto forward = (to - from).normalized();
    auto up_normalized = up.normalized();
    auto left = forward.cross(up_normalized);
    auto true_up = left.cross(forward);

    view_matrix.matrix().block(0, 0, Eigen::fix<1>, Eigen::fix<3>) = left.transpose();
    view_matrix.matrix().block(1, 0, Eigen::fix<1>, Eigen::fix<3>) = true_up.transpose();
    view_matrix.matrix().block(2, 0, Eigen::fix<1>, Eigen::fix<3>) = -forward.transpose();

    view_matrix *= transform::translation(-from.x(), -from.y(), -from.z());

    return view_matrix;
  }

}  // namespace yart
