#include "yart/util/math.h"

#include <gtest/gtest.h>

#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/io.hpp>

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
  auto vector = glm::vec4(1, -1, 0, 0);
  auto normal = glm::vec4(0, 1, 0, 0);

  auto expected = glm::vec4(1, 1, 0, 0);
  auto result = math::reflect(vector, normal);
  ASSERT_TRUE(glm::all(glm::epsilonEqual(result, expected, 1e-6f)))
      << "Expected: " << expected << ", got: " << result;
}

TEST(VectorOperations, ReflectSlanted) {
  auto vector = glm::vec4(0, -1, 0, 0);
  auto normal = glm::vec4(std::sqrt(2) / 2, std::sqrt(2) / 2, 0, 0);

  auto expected = glm::vec4(1, 0, 0, 0);
  auto result = math::reflect(vector, normal);
  ASSERT_TRUE(glm::all(glm::epsilonEqual(result, expected, 1e-6f)))
      << "Expected: " << expected << ", got: " << result;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
