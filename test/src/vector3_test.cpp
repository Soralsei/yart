#include "yart/math/vector3.h"

#include <gtest/gtest.h>

#include "yart/math/math.h"

TEST(Vector3InitTests, CheckCorrectInit) {
  yart::vector::Vector3 test = {1, 1, 1};
  ASSERT_EQ(test, yart::vector::ONE);
  EXPECT_TRUE(true);
}

TEST(Vector3EqualityTests, CheckEquals) {
  yart::vector::Vector3 test = {4, 3, 1};
  yart::vector::Vector3 test2 = {4, 3, 1};
  ASSERT_EQ(test, test2);
  EXPECT_TRUE(true);
}

TEST(Vector3EqualityTests, CheckNotEquals) {
  yart::vector::Vector3 test = {4, 3, 1};
  yart::vector::Vector3 test2 = {4, 3, 0};
  ASSERT_NE(test, test2);
  EXPECT_TRUE(true);
}

TEST(Vector3ArithmeticTests, CheckIncrement) {
  yart::vector::Vector3 test = {4, 3, 1};
  auto result = test + 1.0f;
  yart::vector::Vector3 expected = {5, 4, 2};
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}
TEST(Vector3ArithmeticTests, CheckSelfIncrement) {
  yart::vector::Vector3 test = {4, 3, 1};
  test += 1.0f;
  yart::vector::Vector3 expected = {5, 4, 2};
  ASSERT_EQ(test, expected);
  EXPECT_TRUE(true);
}

TEST(Vector3ArithmeticTests, CheckAddition) {
  yart::vector::Vector3 test = {4, 3, 1};
  auto result = test + yart::vector::ONE;
  yart::vector::Vector3 expected = {5, 4, 2};
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(Vector3ArithmeticTests, CheckSubtraction) {
  yart::vector::Vector3 test = {4, 3, 1};
  auto result = test - yart::vector::ONE;
  yart::vector::Vector3 expected = {3, 2, 0};
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(Vector3ArithmeticTests, CheckSubtractionZero) {
  yart::vector::Vector3 test = {4, 3, 1};
  auto result = test - yart::vector::ZERO;
  ASSERT_EQ(result, test);
  EXPECT_TRUE(true);
}

TEST(Vector3ArithmeticTests, CheckSubtractionSelf) {
  yart::vector::Vector3 test = {4, 3, 1};
  auto result = test - test;
  ASSERT_EQ(result, yart::vector::ZERO);
  EXPECT_TRUE(true);
}

TEST(Vector3ArithmeticTests, CheckMultiplicationOne) {
  yart::vector::Vector3 test = {4, 3, 1};
  auto result = test * yart::vector::ONE;
  ASSERT_EQ(result, test);
  EXPECT_TRUE(true);
}

TEST(Vector3ArithmeticTests, CheckDivisionOne) {
  yart::vector::Vector3 test = {4, 3, 1};
  auto result = test / yart::vector::ONE;
  ASSERT_EQ(result, test);
  EXPECT_TRUE(true);
}

TEST(Vector3ArithmeticTests, CheckSelfMult) {
  yart::vector::Vector3 test = {4, 3, 1};
  test *= yart::vector::Vector3{2, 0, 4};
  yart::vector::Vector3 expected = {8, 0, 4};
  ASSERT_EQ(test, expected);
  EXPECT_TRUE(true);
}

TEST(Vector3ArithmeticTests, CheckSelfDiv) {
  yart::vector::Vector3 test = {4, 3, 1};
  test /= yart::vector::Vector3{2, 1, 4};
  yart::vector::Vector3 expected = {2, 3, 1 / 4.0};
  ASSERT_EQ(test, expected);
  EXPECT_TRUE(true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
