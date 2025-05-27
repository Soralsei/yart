#include "yart/core/camera.h"

#include "yart/core/ray.h"

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

  Ray Camera::ray_to(int x, int y) const {
    // Offset from edge of pixel (index passed as x and y) and center of pixel
    float x_offset = (static_cast<float>(x) + 0.5f) * pixel_size;
    float y_offset = (static_cast<float>(y) + 0.5f) * pixel_size;

    float world_x = half_width - x_offset;
    float world_y = half_height - y_offset;

    Eigen::Matrix4f inverse = transform.matrix().inverse();
    Eigen::Vector4f pixel = inverse * Eigen::Vector3f{world_x, world_y, -1}.homogeneous();
    Eigen::Vector4f origin = inverse * Eigen::Vector3f::Zero().homogeneous();
    // std::cout << "Camera origin: " << origin.transpose() << "\n";
    // std::cout << "Camera transform:\n" << transform.matrix() << "\n";

    Eigen::Vector4f direction = (pixel - origin).normalized();

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

    view_matrix.matrix().block<1, 3>(Eigen::fix<0>, Eigen::fix<0>) = left.transpose();
    view_matrix.matrix().block<1, 3>(Eigen::fix<1>, Eigen::fix<0>) = true_up.transpose();
    view_matrix.matrix().block<1, 3>(Eigen::fix<2>, Eigen::fix<0>) = -forward.transpose();

    view_matrix.translate(-from);

    return view_matrix;
  }

}  // namespace yart
