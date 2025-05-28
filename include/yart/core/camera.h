#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float4.hpp>

#include "yart/core/object3d.h"

namespace yart {
  class Ray;
  class Camera : public Object3D {
  private:
    int hsize;
    int vsize;

    float half_width;
    float half_height;

    float fov;
    float pixel_size;

    // glm::mat4 view_matrix;
    glm::mat4 view_matrix;

  public:
    Camera(int hsize, int vsize, float fov);
    ~Camera() = default;

    Ray ray_to(int x, int y);

    void look_at(const glm::vec3& target, const glm::vec3& up);

    int get_hsize() const;
    int get_vsize() const;
    float get_fov() const;
    float get_pixel_size() const;

    static glm::mat4 get_view_transform(const glm::vec3& from, const glm::vec3& to,
                                        const glm::vec3& up);
  };
}  // namespace yart
