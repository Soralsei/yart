#include "yart/math/transform.h"

#include <gtest/gtest.h>

#include "Eigen/Dense"

using namespace Eigen;

TEST(Transforms, Translation) {
  Matrix4f translation = yart::transform::translation(5.0f, -3.0f, 2.0f);
  Vector4f point;
  point << -3, 4, 5, 1;
  Vector4f expected = {2, 1, 7, 1};
  ASSERT_EQ(translation * point, expected);
}

TEST(Transforms, TranslationInverse) {
  Matrix4f translation = yart::transform::translation(5.0f, -3.0f, 2.0f);
  Vector4f point;
  point << -3, 4, 5, 1;
  Vector4f expected = {-8, 7, 3, 1};
  ASSERT_EQ(translation.inverse() * point, expected);
}

TEST(Transforms, Scaling) {
  Matrix4f scale = yart::transform::scaling(2.0f, 3.0f, 4.0f);
  Vector4f point;
  point << -4, 6, 8, 1;
  Vector4f expected = {-8, 18, 32, 1};
  ASSERT_EQ(scale * point, expected);
}

TEST(Transforms, ScalingInverse) {
  Matrix4f scale = yart::transform::scaling(2.0f, 3.0f, 4.0f);
  Vector4f point;
  point << -4, 6, 8, 1;
  Vector4f expected = {-2, 2, 2, 1};
  ASSERT_EQ(scale.inverse() * point, expected);
}

TEST(Transforms, Reflect) {
  Matrix4f scale = yart::transform::scaling(-1.0f, 1.0f, 1.0f);
  Vector4f point;
  point << 2, 3, 4, 1;
  Vector4f expected = {-2, 3, 4, 1};
  ASSERT_EQ(scale.inverse() * point, expected);
}

TEST(Rotation, RotateX) {
  Matrix4f rotation = yart::transform::rotationX(static_cast<float>(M_PI / 4.0f));
  Vector4f point = {0, 1, 0, 1};
  Vector4f expected = {0, std::sqrt(2) / 2, std::sqrt(2) / 2, 1};
  ASSERT_TRUE((rotation * point).isApprox(expected));
  rotation = yart::transform::rotationX(static_cast<float>(M_PI / 2.0f));
  expected = {0, 0, 1, 1};
  ASSERT_TRUE((rotation * point).isApprox(expected));
}

TEST(Rotation, RotateXInverse) {
  Matrix4f rotation = yart::transform::rotationX(static_cast<float>(M_PI / 4.0f));
  Vector4f point = {0, 1, 0, 1};
  Vector4f expected = {0, std::sqrt(2) / 2, -std::sqrt(2) / 2, 1};
  ASSERT_TRUE((rotation.inverse() * point).isApprox(expected));
}

TEST(Rotation, RotateY) {
  Matrix4f rotation = yart::transform::rotationY(static_cast<float>(M_PI / 4.0f));
  Vector4f point = {0, 0, 1, 1};
  Vector4f expected = {std::sqrt(2) / 2, 0, std::sqrt(2) / 2, 1};
  ASSERT_TRUE((rotation * point).isApprox(expected));
  rotation = yart::transform::rotationY(static_cast<float>(M_PI / 2.0f));
  expected = {1, 0, 0, 1};
  ASSERT_TRUE((rotation * point).isApprox(expected));
}

TEST(Rotation, RotateYInverse) {
  Matrix4f rotation = yart::transform::rotationY(static_cast<float>(M_PI / 4.0f));
  Vector4f point = {0, 0, 1, 1};
  Vector4f expected = {-std::sqrt(2) / 2, 0, std::sqrt(2) / 2, 1};
  ASSERT_TRUE((rotation.inverse() * point).isApprox(expected));
}

TEST(Rotation, RotateZ) {
  Matrix4f rotation = yart::transform::rotationZ(static_cast<float>(M_PI / 4.0f));
  Vector4f point = {0, 1, 0, 1};
  Vector4f expected = {-std::sqrt(2) / 2, std::sqrt(2) / 2, 0, 1};
  ASSERT_TRUE((rotation * point).isApprox(expected));
  rotation = yart::transform::rotationZ(static_cast<float>(M_PI / 2.0f));
  expected = {-1, 0, 0, 1};
  ASSERT_TRUE((rotation * point).isApprox(expected));
}

TEST(Rotation, RotateZInverse) {
  Matrix4f rotation = yart::transform::rotationZ(static_cast<float>(M_PI / 4.0f));
  Vector4f point = {0, 1, 0, 1};
  Vector4f expected = {std::sqrt(2) / 2, std::sqrt(2) / 2, 0, 1};
  ASSERT_TRUE((rotation.inverse() * point).isApprox(expected));
}

TEST(Shear, ShearXY) {
  Matrix4i shear = yart::transform::shear(1, 0, 0, 0, 0, 0);
  Vector4i point = {2, 3, 4, 1};
  Vector4i expected = {5, 3, 4, 1};
  ASSERT_EQ(shear * point, expected);
}

TEST(Shear, ShearXZ) {
  Matrix4i shear = yart::transform::shear(0, 1, 0, 0, 0, 0);
  Vector4i point = {2, 3, 4, 1};
  Vector4i expected = {6, 3, 4, 1};
  ASSERT_EQ(shear * point, expected);
}

TEST(Shear, ShearYX) {
  Matrix4i shear = yart::transform::shear(0, 0, 1, 0, 0, 0);
  Vector4i point = {2, 3, 4, 1};
  Vector4i expected = {2, 5, 4, 1};
  ASSERT_EQ(shear * point, expected);
}

TEST(Shear, ShearYZ) {
  Matrix4i shear = yart::transform::shear(0, 0, 0, 1, 0, 0);
  Vector4i point = {2, 3, 4, 1};
  Vector4i expected = {2, 7, 4, 1};
  ASSERT_EQ(shear * point, expected);
}

TEST(Shear, ShearZX) {
  Matrix4i shear = yart::transform::shear(0, 0, 0, 0, 1, 0);
  Vector4i point = {2, 3, 4, 1};
  Vector4i expected = {2, 3, 6, 1};
  ASSERT_EQ(shear * point, expected);
}

TEST(Shear, ShearZY) {
  Matrix4i shear = yart::transform::shear(0, 0, 0, 0, 0, 1);
  Vector4i point = {2, 3, 4, 1};
  Vector4i expected = {2, 3, 7, 1};
  ASSERT_EQ(shear * point, expected);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}