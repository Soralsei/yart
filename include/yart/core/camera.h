#pragma once
#include "yart/core/object3d.h"

namespace yart {
  class Camera : Object3D {
  private:
    float width;
    float height;
    float fov;
    float pixel_size;

  public:
    Camera(float width, float height, float fov);
    ~Camera();

    float get_pixel_size() const;

    void look_at(Eigen::Vector3f target, Eigen::Vector3f up);

    static Eigen::Matrix4f get_view_matrix(Eigen::Vector3f from, Eigen::Vector3f to,
                                           Eigen::Vector3f up);
  };
}  // namespace yart
