#include "yart/image/color.h"

#include <gtest/gtest.h>

using namespace yart;

TEST(ColorTest, ColorAddition) {
  image::Color c1(0.5f, 0.5f, 0.5f);
  image::Color c2(0.5f, 0.5f, 0.5f);
  image::Color expected(1.0f, 1.0f, 1.0f);
  image::Color result = c1 + c2;
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(ColorTest, ColorSubtraction) {
  image::Color c1(1.0f, 1.0f, 1.0f);
  image::Color c2(0.7f, 0.2f, 0.5f);
  image::Color expected(0.3f, 0.8f, 0.5f);
  image::Color result = c1 - c2;
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(ColorTest, ColorHadamardProduct) {
  image::Color c1(1, 0.2, 0.4);
  image::Color c2(0.9, 1, 0.1);
  image::Color expected(0.9, 0.2, 0.04);
  image::Color result = c1 * c2;
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(ColorTest, ColorScalarMultiplication) {
  image::Color c(0.2f, 0.3f, 0.4f);
  float scalar = 2.0f;
  image::Color expected(0.4f, 0.6f, 0.8f);
  image::Color result = c * scalar;
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(ColorTest, ColorEquality) {
  image::Color c1(0.5f, 0.5f, 0.5f);
  image::Color c2(0.5f, 0.5f, 0.5f);
  ASSERT_EQ(c1, c2);
  EXPECT_TRUE(true);
}

TEST(ColorTest, ColorInequality) {
  image::Color c1(0.5f, 0.5f, 0.5f);
  image::Color c2(0.5f, 0.6f, 0.5f);
  ASSERT_NE(c1, c2);
  EXPECT_TRUE(true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
