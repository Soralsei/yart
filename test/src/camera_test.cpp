#include "yart/core/camera.hpp"

#include <gtest/gtest.h>

#include <cmath>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_relational.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/io.hpp>
#include <glm/matrix.hpp>
#include <iostream>

#include "yart/core/ray.hpp"
#include "yart/core/world.hpp"
#include "yart/image/canvas.hpp"

using namespace yart;

TEST(ViewMatrix, Identity) {
  glm::vec3 from{0, 0, 0};
  glm::vec3 to{0, 0, -1};
  glm::vec3 up{0, 1, 0};

  glm::mat4 view = Camera::get_view_transform(from, to, up);

  ASSERT_TRUE(glm::all(glm::equal(view, glm::mat4{1.0f}, 1e-6f)))
      << "Expected Identity view matrix, got : " << view;
}

TEST(ViewMatrix, Mirror) {
  glm::vec3 from{0, 0, 0};
  glm::vec3 to{0, 0, 1};
  glm::vec3 up{0, 1, 0};

  auto view = Camera::get_view_transform(from, to, up);
  auto expected = geometry::Transform{};
  expected.scale(glm::vec3{-1, 1, -1});

  ASSERT_TRUE(glm::all(glm::equal(view, expected.matrix(), 1e-6f)))
      << "Expected " << expected.matrix() << " view matrix, got : " << view;
}

TEST(ViewMatrix, Translation) {
  glm::vec3 from{0, 0, 8};
  glm::vec3 to{0, 0, 0};
  glm::vec3 up{0, 1, 0};

  auto view = Camera::get_view_transform(from, to, up);
  auto expected = geometry::Transform{};
  expected.translate(glm::vec3{0, 0, -8});

  ASSERT_TRUE(glm::all(glm::equal(view, expected.matrix(), 1e-6f)))
      << "Expected " << expected.matrix() << " view matrix, got : " << view;
}

TEST(ViewMatrix, Arbitrary) {
  glm::vec3 from{1, 3, 2};
  glm::vec3 to{4, -2, 8};
  glm::vec3 up{1, 1, 0};

  auto view = Camera::get_view_transform(from, to, up);
  // clang-format off
  glm::mat4 expected{
    -0.514, 0.514, 0.686, -2.401,
    0.779, 0.615, 0.123, -2.870,
    -0.359, 0.598, -0.717, 0.000,
    0.000, 0.000, 0.000, 1.000
  };
  expected = glm::transpose(expected); // Transpose to match glm's column-major order
  // clang-format on

  ASSERT_TRUE(glm::all(glm::equal(view, expected, 1e-3f)))
      << "Expected " << expected << " view matrix, got : " << view;
}

TEST(CameraTests, Initialization) {
  int hsize = 160;
  int vsize = 120;
  float fov = M_PI_2;

  Camera cam{hsize, vsize, fov};

  ASSERT_FLOAT_EQ(cam.get_hsize(), hsize);
  ASSERT_FLOAT_EQ(cam.get_vsize(), vsize);
  ASSERT_FLOAT_EQ(cam.get_fov(), fov);

  ASSERT_TRUE(glm::all(glm::equal(cam.transform.matrix(), glm::mat4{1.0f}, 1e-6f)))
      << "Expected Identity transform matrix, got : " << cam.transform.matrix();
}

TEST(CameraTests, PixelSizeHorizontal) {
  int hsize = 200;
  int vsize = 125;
  float fov = M_PI_2;

  Camera cam{hsize, vsize, fov};
  ASSERT_FLOAT_EQ(cam.get_pixel_size(), 0.01);
}

TEST(CameraTests, PixelSizeVertical) {
  int hsize = 125;
  int vsize = 200;
  float fov = M_PI_2;

  Camera cam{hsize, vsize, fov};
  ASSERT_FLOAT_EQ(cam.get_pixel_size(), 0.01);
}

TEST(CameraTests, RayCentered) {
  int hsize = 201;
  int vsize = 101;
  float fov = M_PI_2;

  Camera cam{hsize, vsize, fov};
  auto ray = cam.ray_to(100, 50);

  std::cout << ray << '\n';

  ASSERT_TRUE(glm::all(glm::equal(ray.get_origin(), glm::vec4{0, 0, 0, 1})));
  ASSERT_TRUE(glm::all(glm::equal(ray.get_direction(), glm::vec4{0.0f, 0.0f, -1.0f, 0.0f}, 1e-3f)));
}

TEST(CameraTests, RayCorner) {
  int hsize = 201;
  int vsize = 101;
  float fov = M_PI_2;

  Camera cam{hsize, vsize, fov};
  auto ray = cam.ray_to(0, 0);
  std::cout << ray << '\n';

  ASSERT_TRUE(glm::all(glm::equal(ray.get_origin(), glm::vec4{0, 0, 0, 1})));
  ASSERT_TRUE(
      glm::all(glm::equal(ray.get_direction(), glm::vec4{0.66519, 0.33259, -0.66851, 0}, 1e-3f)));
}

TEST(CameraTests, RayTransformedCamera) {
  int hsize = 201;
  int vsize = 101;
  float fov = M_PI_2;

  Camera cam{hsize, vsize, fov};
  geometry::Transform transform;
  transform.rotate_y(M_PI_4f).translate(glm::vec3{0, -2, 5});
  cam.transform = transform;
  Ray ray = cam.ray_to(100, 50);
  std::cout << ray << '\n';

  ASSERT_TRUE(glm::all(glm::equal(ray.get_origin(), glm::vec4{0, 2, -5, 1}, 1e-3f)));
  ASSERT_TRUE(glm::all(glm::equal(
      ray.get_direction(), glm::vec4{std::sqrt(2.0f) / 2, 0, -std::sqrt(2.0f) / 2, 0}, 1e-3f)));
}

TEST(CameraTests, RenderWorld) {
  auto world = World::default_world();
  auto camera = Camera{11, 11, M_PI_2};
  camera.transform = geometry::Transform{};
  camera.transform.set_local_position(glm::vec3{0, 0, -5});

  auto target = glm::vec3{};
  auto up = glm::vec3{0, 1, 0};

  camera.look_at(target, up);
  auto image = world->render(camera);
  // file::PPMWriter writer;
  // writer.write("test_output.ppm", image->getPixels(), image->getWidth(), image->getHeight());

  ASSERT_EQ(image->getPixel(5, 5), (color::Color{0.38066, 0.47583, 0.2855}));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}