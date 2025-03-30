#include "yart/rendering/color.h"

#include <gtest/gtest.h>

using namespace yart;

TEST(ColorTest, ColorAddition) {
  rendering::Color c1(0.5f, 0.5f, 0.5f);
  rendering::Color c2(0.5f, 0.5f, 0.5f);
  rendering::Color expected(1.0f, 1.0f, 1.0f);
  rendering::Color result = c1 + c2;
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(ColorTest, ColorSubtraction) {
  rendering::Color c1(1.0f, 1.0f, 1.0f);
  rendering::Color c2(0.7f, 0.2f, 0.5f);
  rendering::Color expected(0.3f, 0.8f, 0.5f);
  rendering::Color result = c1 - c2;
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(ColorTest, ColorHadamardProduct) {
  rendering::Color c1(1, 0.2, 0.4);
  rendering::Color c2(0.9, 1, 0.1);
  rendering::Color expected(0.9, 0.2, 0.04);
  rendering::Color result = c1 * c2;
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(ColorTest, ColorScalarMultiplication) {
  rendering::Color c(0.2f, 0.3f, 0.4f);
  float scalar = 2.0f;
  rendering::Color expected(0.4f, 0.6f, 0.8f);
  rendering::Color result = c * scalar;
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(ColorTest, ColorEquality) {
  rendering::Color c1(0.5f, 0.5f, 0.5f);
  rendering::Color c2(0.5f, 0.5f, 0.5f);
  ASSERT_EQ(c1, c2);
  EXPECT_TRUE(true);
}

TEST(ColorTest, ColorInequality) {
  rendering::Color c1(0.5f, 0.5f, 0.5f);
  rendering::Color c2(0.5f, 0.6f, 0.5f);
  ASSERT_NE(c1, c2);
  EXPECT_TRUE(true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
