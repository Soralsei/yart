#include "yart/geometry/transform.h"

#include <gtest/gtest.h>

#include "Eigen/Dense"

using namespace Eigen;

TEST(Transforms, Translation) {
  auto translation = yart::transform::translation(5.0f, -3.0f, 2.0f);
  Vector3f point;
  point << -3, 4, 5;
  Vector3f expected = {2, 1, 7};
  ASSERT_EQ(translation * point, expected);
}

TEST(Transforms, TranslationInverse) {
  auto translation = yart::transform::translation(5.0f, -3.0f, 2.0f);
  Vector3f point;
  point << -3, 4, 5;
  Vector3f expected = {-8, 7, 3};
  ASSERT_EQ(translation.inverse() * point, expected);
}

TEST(Transforms, Scaling) {
  auto scale = yart::transform::scale(2.0f, 3.0f, 4.0f);
  Vector3f point;
  point << -4, 6, 8;
  Vector3f expected = {-8, 18, 32};
  ASSERT_EQ(scale * point, expected);
}

TEST(Transforms, ScalingInverse) {
  Matrix3f scale = yart::transform::scale(2.0f, 3.0f, 4.0f);
  Vector3f point;
  point << -4, 6, 8;
  Vector3f expected = {-2, 2, 2};
  ASSERT_EQ(scale.inverse() * point, expected);
}

TEST(Transforms, Reflect) {
  Matrix3f scale = yart::transform::scale(-1.0f, 1.0f, 1.0f);
  Vector3f point;
  point << 2, 3, 4;
  Vector3f expected = {-2, 3, 4};
  ASSERT_EQ(scale.inverse() * point, expected);
}

TEST(Rotation, RotateX) {
  Matrix3f rotation
      = yart::transform::rotationX(static_cast<float>(M_PI / 4.0f)).toRotationMatrix();
  Vector3f point = {0, 1, 0};
  Vector3f expected = {0, std::sqrt(2.0f) / 2, std::sqrt(2.0f) / 2};
  ASSERT_TRUE((rotation * point).isApprox(expected));
  rotation = yart::transform::rotationX(static_cast<float>(M_PI / 2.0f));
  expected = {0, 0, 1};
  ASSERT_TRUE((rotation * point).isApprox(expected));
}

TEST(Rotation, RotateXInverse) {
  Matrix3f rotation
      = yart::transform::rotationX(static_cast<float>(M_PI / 4.0f)).toRotationMatrix();
  Vector3f point = {0, 1, 0};
  Vector3f expected = {0, std::sqrt(2.0f) / 2, -std::sqrt(2.0f) / 2};
  ASSERT_TRUE((rotation.inverse() * point).isApprox(expected));
}

TEST(Rotation, RotateY) {
  Matrix3f rotation
      = yart::transform::rotationY(static_cast<float>(M_PI / 4.0f)).toRotationMatrix();
  Vector3f point = {0, 0, 1};
  Vector3f expected = {std::sqrt(2.0f) / 2, 0, std::sqrt(2.0f) / 2};
  ASSERT_TRUE((rotation * point).isApprox(expected));
  rotation = yart::transform::rotationY(static_cast<float>(M_PI / 2.0f));
  expected = {1, 0, 0};
  ASSERT_TRUE((rotation * point).isApprox(expected));
}

TEST(Rotation, RotateYInverse) {
  Matrix3f rotation
      = yart::transform::rotationY(static_cast<float>(M_PI / 4.0f)).toRotationMatrix();
  Vector3f point = {0, 0, 1};
  Vector3f expected = {-std::sqrt(2.0f) / 2, 0, std::sqrt(2.0f) / 2};
  ASSERT_TRUE((rotation.inverse() * point).isApprox(expected));
}

TEST(Rotation, RotateZ) {
  Matrix3f rotation
      = yart::transform::rotationZ(static_cast<float>(M_PI / 4.0f)).toRotationMatrix();
  Vector3f point = {0, 1, 0};
  Vector3f expected = {-std::sqrt(2.0f) / 2, std::sqrt(2.0f) / 2, 0};
  ASSERT_TRUE((rotation * point).isApprox(expected));
  rotation = yart::transform::rotationZ(static_cast<float>(M_PI / 2.0f));
  expected = {-1, 0, 0};
  ASSERT_TRUE((rotation * point).isApprox(expected));
}

TEST(Rotation, RotateZInverse) {
  Matrix3f rotation
      = yart::transform::rotationZ(static_cast<float>(M_PI / 4.0f)).toRotationMatrix();
  Vector3f point = {0, 1, 0};
  Vector3f expected = {std::sqrt(2.0f) / 2, std::sqrt(2.0f) / 2, 0};
  ASSERT_TRUE((rotation.inverse() * point).isApprox(expected));
}

TEST(Shear, ShearXY) {
  Matrix3i shear = yart::transform::shear(1, 0, 0, 0, 0, 0);
  Vector3i point = {2, 3, 4};
  Vector3i expected = {5, 3, 4};
  ASSERT_EQ(shear * point, expected);
}

TEST(Shear, ShearXZ) {
  Matrix3i shear = yart::transform::shear(0, 1, 0, 0, 0, 0);
  Vector3i point = {2, 3, 4};
  Vector3i expected = {6, 3, 4};
  ASSERT_EQ(shear * point, expected);
}

TEST(Shear, ShearYX) {
  Matrix3i shear = yart::transform::shear(0, 0, 1, 0, 0, 0);
  Vector3i point = {2, 3, 4};
  Vector3i expected = {2, 5, 4};
  ASSERT_EQ(shear * point, expected);
}

TEST(Shear, ShearYZ) {
  Matrix3i shear = yart::transform::shear(0, 0, 0, 1, 0, 0);
  Vector3i point = {2, 3, 4};
  Vector3i expected = {2, 7, 4};
  ASSERT_EQ(shear * point, expected);
}

TEST(Shear, ShearZX) {
  Matrix3i shear = yart::transform::shear(0, 0, 0, 0, 1, 0);
  Vector3i point = {2, 3, 4};
  Vector3i expected = {2, 3, 6};
  ASSERT_EQ(shear * point, expected);
}

TEST(Shear, ShearZY) {
  Matrix3i shear = yart::transform::shear(0, 0, 0, 0, 0, 1);
  Vector3i point = {2, 3, 4};
  Vector3i expected = {2, 3, 7};
  ASSERT_EQ(shear * point, expected);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}