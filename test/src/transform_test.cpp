#include "yart/geometry/transform.h"

#include <gtest/gtest.h>

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/io.hpp>

TEST(Transforms, Translation) {
  glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, -3.0f, 2.0f));
  glm::vec4 point{-3, 4, 5, 1};
  glm::vec4 expected = {2, 1, 7, 1};
  ASSERT_EQ(translation * point, expected);
}

TEST(Transforms, TranslationInverse) {
  glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, -3.0f, 2.0f));
  glm::vec4 point{-3, 4, 5, 1};
  glm::vec4 expected = {-8, 7, 3, 1};
  ASSERT_EQ(glm::inverse(translation) * point, expected);
}

TEST(Transforms, Scaling) {
  auto scale = glm::scale(glm::mat4{1.0f}, {2.0f, 3.0f, 4.0f});
  glm::vec4 point{-4, 6, 8, 1};
  glm::vec4 expected = {-8, 18, 32, 1};
  ASSERT_EQ(scale * point, expected);
}

TEST(Transforms, ScalingInverse) {
  glm::mat4 scale = glm::scale(glm::mat4{1.0f}, {2.0f, 3.0f, 4.0f});
  glm::vec4 point{-4, 6, 8, 1};
  glm::vec4 expected = {-2, 2, 2, 1};
  ASSERT_EQ(glm::inverse(scale) * point, expected);
}

TEST(Transforms, Reflect) {
  glm::mat4 scale = glm::scale(glm::mat4{1.0f}, {-1.0f, 1.0f, 1.0f});
  glm::vec4 point{2, 3, 4, 1};
  glm::vec4 expected{-2, 3, 4, 1};
  ASSERT_EQ(glm::inverse(scale) * point, expected);
}

TEST(Rotation, RotateX) {
  glm::quat rotation = glm::angleAxis(M_PI_4f, glm::vec3(1.0f, 0.0f, 0.0f));
  glm::vec4 point = {0, 1, 0, 1};
  glm::vec4 expected = {0, std::sqrt(2.0f) / 2, std::sqrt(2.0f) / 2, 1};
  auto rotated_point = rotation * point;
  ASSERT_TRUE(glm::all(glm::epsilonEqual(rotated_point, expected, 1e-6f)))
      << "Expected " << expected << ", got " << rotated_point;
  rotation = glm::angleAxis(M_PI_2f, glm::vec3(1.0f, 0.0f, 0.0f));
  expected = {0, 0, 1, 1};
  rotated_point = rotation * point;
  ASSERT_TRUE(glm::all(glm::epsilonEqual(rotated_point, expected, 1e-6f)))
      << "Expected " << expected << ", got " << rotated_point;
}

TEST(Rotation, RotateXInverse) {
  glm::quat rotation = glm::angleAxis(M_PI_4f, glm::vec3{1.0f, 0.0f, 0.0f});
  glm::vec4 point = {0, 1, 0, 1};
  glm::vec4 expected = {0, std::sqrt(2.0f) / 2, -std::sqrt(2.0f) / 2, 1};
  auto rotated_point = glm::inverse(rotation) * point;
  ASSERT_TRUE(glm::all(glm::epsilonEqual(rotated_point, expected, 1e-6f)))
      << "Expected " << expected << ", got " << rotated_point;
}

TEST(Rotation, RotateY) {
  glm::quat rotation = glm::angleAxis(M_PI_4f, glm::vec3{0, 1, 0});
  glm::vec4 point = {0, 0, 1, 1};
  glm::vec4 expected = {std::sqrt(2.0f) / 2, 0, std::sqrt(2.0f) / 2, 1};
  ASSERT_TRUE(glm::all(glm::epsilonEqual(rotation * point, expected, 1e-6f)));
  rotation = glm::angleAxis(M_PI_2f, glm::vec3{0, 1, 0});
  expected = {1, 0, 0, 1};
  ASSERT_TRUE(glm::all(glm::epsilonEqual(rotation * point, expected, 1e-6f)));
}

TEST(Rotation, RotateYInverse) {
  glm::quat rotation = glm::angleAxis(M_PI_4f, glm::vec3{0, 1, 0});
  glm::vec4 point = {0, 0, 1, 1};
  glm::vec4 expected = {-std::sqrt(2.0f) / 2, 0, std::sqrt(2.0f) / 2, 1};
  auto rotated_point = glm::inverse(rotation) * point;
  ASSERT_TRUE(glm::all(glm::epsilonEqual(rotated_point, expected, 1e-6f)))
      << "Expected " << expected << ", got " << rotated_point;
}

TEST(Rotation, RotateZ) {
  glm::quat rotation = glm::angleAxis(M_PI_4f, glm::vec3{0, 0, 1});
  glm::vec4 point = {0, 1, 0, 1};
  glm::vec4 expected = {-std::sqrt(2.0f) / 2, std::sqrt(2.0f) / 2, 0, 1};
  ASSERT_TRUE(glm::all(glm::epsilonEqual(rotation * point, expected, 1e-6f)));
  rotation = glm::angleAxis(M_PI_2f, glm::vec3{0, 0, 1});
  expected = {-1, 0, 0, 1};
  ASSERT_TRUE(glm::all(glm::epsilonEqual(rotation * point, expected, 1e-6f)));
}

TEST(Rotation, RotateZInverse) {
  glm::quat rotation = glm::angleAxis(M_PI_4f, glm::vec3{0, 0, 1});
  glm::vec4 point = {0, 1, 0, 1};
  glm::vec4 expected = {std::sqrt(2.0f) / 2, std::sqrt(2.0f) / 2, 0, 1};
  ASSERT_TRUE(glm::all(glm::epsilonEqual(glm::inverse(rotation) * point, expected, 1e-6f)));
}

TEST(Shear, ShearXY) {
  glm::mat4 shear = yart::transform::shear(1, 0, 0, 0, 0, 0);
  glm::vec4 point = {2, 3, 4, 1};
  glm::vec4 expected = {5, 3, 4, 1};
  ASSERT_EQ(shear * point, expected);
}

TEST(Shear, ShearXZ) {
  glm::mat4 shear = yart::transform::shear(0, 1, 0, 0, 0, 0);
  glm::vec4 point = {2, 3, 4, 1};
  glm::vec4 expected = {6, 3, 4, 1};
  ASSERT_EQ(shear * point, expected);
}

TEST(Shear, ShearYX) {
  glm::mat4 shear = yart::transform::shear(0, 0, 1, 0, 0, 0);
  glm::vec4 point = {2, 3, 4, 1};
  glm::vec4 expected = {2, 5, 4, 1};
  ASSERT_EQ(shear * point, expected);
}

TEST(Shear, ShearYZ) {
  glm::mat4 shear = yart::transform::shear(0, 0, 0, 1, 0, 0);
  glm::vec4 point = {2, 3, 4, 1};
  glm::vec4 expected = {2, 7, 4, 1};
  ASSERT_EQ(shear * point, expected);
}

TEST(Shear, ShearZX) {
  glm::mat4 shear = yart::transform::shear(0, 0, 0, 0, 1, 0);
  glm::vec4 point = {2, 3, 4, 1};
  glm::vec4 expected = {2, 3, 6, 1};
  ASSERT_EQ(shear * point, expected);
}

TEST(Shear, ShearZY) {
  glm::mat4 shear = yart::transform::shear(0, 0, 0, 0, 0, 1);
  glm::vec4 point = {2, 3, 4, 1};
  glm::vec4 expected = {2, 3, 7, 1};
  ASSERT_EQ(shear * point, expected);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}