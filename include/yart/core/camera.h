#pragma once
#include "yart/core/object3d.h"

namespace yart {
  class Ray;
  class Camera : public Object3D {
  private:
    float hsize;
    float vsize;

    float half_width;
    float half_height;

    float fov;
    float pixel_size;

    Eigen::Matrix4f view_matrix;

  public:
    Camera(float hsize, float vsize, float fov);
    ~Camera() = default;

    Ray ray_to(int x, int y) const;

    void look_at(const Eigen::Vector3f& target, const Eigen::Vector3f& up);

    uint32_t get_hsize() const;
    uint32_t get_vsize() const;
    float get_fov() const;
    float get_pixel_size() const;

    static geometry::Transform3D get_view_transform(const Eigen::Vector3f& from,
                                                    const Eigen::Vector3f& to,
                                                    const Eigen::Vector3f& up);
  };
}  // namespace yart
