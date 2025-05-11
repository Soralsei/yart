#include "yart/util/math.h"

#include <gtest/gtest.h>
using namespace yart;

TEST(RemapTest, FloatToInt) {
  float value = 5.0f;
  float old_min = 0.0f;
  float old_max = 10.0f;
  int new_min = -5;
  int new_max = 5;
  int expected = 0;
  int result = math::remap(value, old_min, old_max, new_min, new_max);
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(RemapTest, IntToFloat) {
  int value = 5;
  int old_min = 0;
  int old_max = 10;
  float new_min = 0.0f;
  float new_max = 5;
  float expected = 2.5f;
  float result = math::remap(value, old_min, old_max, new_min, new_max);
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(RemapTest, Byte255ToFloat) {
  uint8_t value = 255;
  uint8_t old_min = 0;
  uint8_t old_max = 255;
  float new_min = 0.0f;
  float new_max = 1.0f;
  float expected = 1.0f;
  float result = math::remap(value, old_min, old_max, new_min, new_max);
  ASSERT_EQ(math::approx_equals(result, expected), true);
  EXPECT_TRUE(true);
}

TEST(RemapTest, Byte128ToFloat) {
  uint8_t value = 128;
  uint8_t old_min = 0;
  uint8_t old_max = 255;
  float new_min = 0.0f;
  float new_max = 1.0f;
  float expected = 0.5019607843f;
  float result = math::remap(value, old_min, old_max, new_min, new_max);
  ASSERT_EQ(math::approx_equals(result, expected), true);
  EXPECT_TRUE(true);
}

TEST(VectorOperations, Reflect45) {
  auto vector = Eigen::Vector3f(1, -1, 0);
  auto normal = Eigen::Vector3f(0, 1, 0);

  auto expected = Eigen::Vector3f(1, 1, 0);
  auto result = math::reflect(vector, normal);
  ASSERT_TRUE(result.isApprox(expected, 1e-6));
}

TEST(VectorOperations, ReflectSlanted) {
  auto vector = Eigen::Vector3f(0, -1, 0);
  auto normal = Eigen::Vector3f(std::sqrt(2) / 2, std::sqrt(2) / 2, 0);

  auto expected = Eigen::Vector3f(1, 0, 0);
  auto result = math::reflect(vector, normal);
  ASSERT_TRUE(result.isApprox(expected, 1e-6));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
