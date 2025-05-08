#include "yart/image/color.h"

#include <gtest/gtest.h>

using namespace yart;

TEST(ColorTest, ColorAddition) {
  color::Color c1(0.5f, 0.5f, 0.5f);
  color::Color c2(0.5f, 0.5f, 0.5f);
  color::Color expected(1.0f, 1.0f, 1.0f);
  color::Color result = c1 + c2;
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(ColorTest, ColorSubtraction) {
  color::Color c1(1.0f, 1.0f, 1.0f);
  color::Color c2(0.7f, 0.2f, 0.5f);
  color::Color expected(0.3f, 0.8f, 0.5f);
  color::Color result = c1 - c2;
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(ColorTest, ColorHadamardProduct) {
  color::Color c1(1, 0.2, 0.4);
  color::Color c2(0.9, 1, 0.1);
  color::Color expected(0.9, 0.2, 0.04);
  color::Color result = c1 * c2;
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(ColorTest, ColorScalarMultiplication) {
  color::Color c(0.2f, 0.3f, 0.4f);
  float scalar = 2.0f;
  color::Color expected(0.4f, 0.6f, 0.8f);
  color::Color result = c * scalar;
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(ColorTest, ColorEquality) {
  color::Color c1(0.5f, 0.5f, 0.5f);
  color::Color c2(0.5f, 0.5f, 0.5f);
  ASSERT_EQ(c1, c2);
  EXPECT_TRUE(true);
}

TEST(ColorTest, ColorInequality) {
  color::Color c1(0.5f, 0.5f, 0.5f);
  color::Color c2(0.5f, 0.6f, 0.5f);
  ASSERT_NE(c1, c2);
  EXPECT_TRUE(true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
