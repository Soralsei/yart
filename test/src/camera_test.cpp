#include "yart/core/camera.h"

#include <gtest/gtest.h>

#include <iostream>

#include "Eigen/Dense"
#include "yart/core/ray.h"
#include "yart/core/world.h"
#include "yart/file/ppm_writer.h"
#include "yart/geometry/transform.h"
#include "yart/image/canvas.h"

using namespace yart;

TEST(ViewMatrix, Identity) {
  Eigen::Vector3f from{0, 0, 0};
  Eigen::Vector3f to{0, 0, -1};
  Eigen::Vector3f up{0, 1, 0};

  auto view = Camera::get_view_transform(from, to, up);

  ASSERT_TRUE(view.isApprox(decltype(view)::Identity()))
      << "Expected Identity view matrix, got : " << view.matrix();
}

TEST(ViewMatrix, Mirror) {
  Eigen::Vector3f from{0, 0, 0};
  Eigen::Vector3f to{0, 0, 1};
  Eigen::Vector3f up{0, 1, 0};

  auto view = Camera::get_view_transform(from, to, up);
  auto expected = geometry::Transform3D{transform::scale<float>(-1, 1, -1)};

  ASSERT_TRUE(view.isApprox(expected))
      << "Expected " << expected.matrix() << " view matrix, got : " << view.matrix();
}

TEST(ViewMatrix, Translation) {
  Eigen::Vector3f from{0, 0, 8};
  Eigen::Vector3f to{0, 0, 0};
  Eigen::Vector3f up{0, 1, 0};

  auto view = Camera::get_view_transform(from, to, up);
  auto expected = geometry::Transform3D{transform::translation<float>(0, 0, -8)};

  ASSERT_TRUE(view.isApprox(expected))
      << "Expected " << expected.matrix() << " view matrix, got : " << view.matrix();
}

TEST(ViewMatrix, Arbitrary) {
  Eigen::Vector3f from{1, 3, 2};
  Eigen::Vector3f to{4, -2, 8};
  Eigen::Vector3f up{1, 1, 0};

  auto view = Camera::get_view_transform(from, to, up);
  Eigen::Matrix4f expected;
  expected << -0.50709, 0.50709, 0.67612, -2.36643, 0.76772, 0.60609, 0.12122, -2.82843, -0.35857,
      0.59761, -0.71714, 0.00000, 0.00000, 0.00000, 0.00000, 1.00000;

  ASSERT_TRUE(view.matrix().isApprox(expected))
      << "Expected " << expected << " view matrix, got : " << view.matrix();
}

TEST(CameraTests, Initialization) {
  float hsize = 160;
  float vsize = 120;
  float fov = M_PI_2;

  Camera cam{hsize, vsize, fov};

  ASSERT_FLOAT_EQ(cam.get_hsize(), hsize);
  ASSERT_FLOAT_EQ(cam.get_vsize(), vsize);
  ASSERT_FLOAT_EQ(cam.get_fov(), fov);

  ASSERT_TRUE(cam.transform.isApprox(geometry::Transform3D::Identity()));
}

TEST(CameraTests, PixelSizeHorizontal) {
  float hsize = 200;
  float vsize = 125;
  float fov = M_PI_2;

  Camera cam{hsize, vsize, fov};
  ASSERT_FLOAT_EQ(cam.get_pixel_size(), 0.01);
}

TEST(CameraTests, PixelSizeVertical) {
  float hsize = 125;
  float vsize = 200;
  float fov = M_PI_2;

  Camera cam{hsize, vsize, fov};
  ASSERT_FLOAT_EQ(cam.get_pixel_size(), 0.01);
}

TEST(CameraTests, RayCentered) {
  float hsize = 201;
  float vsize = 101;
  float fov = M_PI_2;

  Camera cam{hsize, vsize, fov};
  auto ray = cam.ray_to(100, 50);

  std::cout << ray << '\n';

  ASSERT_TRUE(ray.get_origin().isApprox(Eigen::Vector3f::Zero().homogeneous()));
  ASSERT_TRUE(ray.get_direction().isApprox(Eigen::Vector4f{0, 0, -1, 0}));
}

TEST(CameraTests, RayCorner) {
  float hsize = 201;
  float vsize = 101;
  float fov = M_PI_2;

  Camera cam{hsize, vsize, fov};
  auto ray = cam.ray_to(0, 0);
  std::cout << ray << '\n';

  ASSERT_TRUE(ray.get_origin().isApprox(Eigen::Vector3f::Zero().homogeneous()));
  ASSERT_TRUE(ray.get_direction().isApprox(Eigen::Vector4f{{0.66519, 0.33259, -0.66851, 0}}));
}

TEST(CameraTests, RayTransformedCamera) {
  float hsize = 201;
  float vsize = 101;
  float fov = M_PI_2;

  Camera cam{hsize, vsize, fov};
  geometry::Transform3D transform
      = transform::rotationY<float>(M_PI_4) * transform::translation<float>(0, -2, 5);
  // geometry::Transform3D transform{t};
  cam.transform = transform;
  Ray ray = cam.ray_to(100, 50);
  std::cout << ray << '\n';

  ASSERT_TRUE(ray.get_origin().isApprox(Eigen::Vector3f{0, 2, -5}.homogeneous()));
  ASSERT_TRUE(
      ray.get_direction().isApprox(Eigen::Vector4f{std::sqrt(2) / 2, 0, -std::sqrt(2) / 2, 0}));
}

TEST(CameraTests, RenderWorld) {
  auto world = World::default_world();
  auto camera = Camera{11, 11, M_PI_2};
  camera.transform = geometry::Transform3D{transform::translation<float>(0, 0, -5)};

  auto target = Eigen::Vector3f::Zero();
  auto up = Eigen::Vector3f::UnitY();

  camera.look_at(target, up);
  auto image = world->render(camera);
  file::PPMWriter writer;
  writer.write("test_output.ppm", image->getPixels(), image->getWidth(), image->getHeight());

  ASSERT_EQ(image->getPixel(5, 5), (color::Color{0.38066, 0.47583, 0.2855}));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}