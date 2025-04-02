#include "yart/math/vector4.h"
#include "yart/math/math.h"

#include <gtest/gtest.h>

TEST(InitTests, CheckCorrectInit) {
  yart::vector::Vector4 test = {1, 1, 1, 1};
  ASSERT_EQ(test, yart::vector::Vector4::ONE);
  EXPECT_TRUE(true);
}

TEST(EqualityTests, CheckEquals) {
  yart::vector::Vector4 test = {4, 3, 2, 1};
  yart::vector::Vector4 test2 = {4, 3, 2, 1};
  ASSERT_EQ(test, test2);
  EXPECT_TRUE(true);
}

TEST(EqualityTests, CheckNotEquals) {
  yart::vector::Vector4 test = {4, 3, 2, 1};
  yart::vector::Vector4 test2 = {4, 2, 1, 3};
  ASSERT_NE(test, test2);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckIncrement) {
  yart::vector::Vector4 test = {4, 3, 2, 1};
  auto result = test + 1.0f;
  yart::vector::Vector4 expected = {5, 4, 3, 2};
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}
TEST(ArithmeticTests, CheckSelfIncrement) {
  yart::vector::Vector4 test = {4, 3, 2, 1};
  test += 1.0f;
  yart::vector::Vector4 expected = {5, 4, 3, 2};
  ASSERT_EQ(test, expected);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckAddition) {
  yart::vector::Vector4 test = {4, 3, 2, 1};
  auto result = test + yart::vector::Vector4::ONE;
  yart::vector::Vector4 expected = {5, 4, 3, 2};
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckSubtraction) {
  yart::vector::Vector4 test = {4, 3, 2, 1};
  auto result = test - yart::vector::Vector4::ONE;
  yart::vector::Vector4 expected = {3, 2, 1, 0};
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckSubtractionZero) {
  yart::vector::Vector4 test = {4, 3, 2, 1};
  auto result = test - yart::vector::Vector4::ZERO;
  ASSERT_EQ(result, test);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckSubtractionSelf) {
  yart::vector::Vector4 test = {4, 3, 2, 1};
  auto result = test - test;
  ASSERT_EQ(result, yart::vector::Vector4::ZERO);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckMultiplicationOne) {
  yart::vector::Vector4 test = {4, 3, 2, 1};
  auto result = test * yart::vector::Vector4::ONE;
  ASSERT_EQ(result, test);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckDivisionOne) {
  yart::vector::Vector4 test = {4, 3, 2, 1};
  auto result = test / yart::vector::Vector4::ONE;
  ASSERT_EQ(result, test);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckSelfMult) {
  yart::vector::Vector4 test = {4, 3, 2, 1};
  test *= yart::vector::Vector4{2, 0, 0, 8};
  yart::vector::Vector4 expected = {8, 0, 0, 8};
  ASSERT_EQ(test, expected);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckSelfDiv) {
  yart::vector::Vector4 test = {4, 3, 2, 1};
  test /= yart::vector::Vector4{2, 1, 2, 4};
  yart::vector::Vector4 expected = {2, 3, 1, 1 / 4.0f};
  ASSERT_EQ(test, expected);
  EXPECT_TRUE(true);
}

TEST(OperationTests, CheckNormOneX) {
  yart::vector::Vector4 test = {1, 0, 0, 0};
  ASSERT_EQ(test.norm(), 1);
  EXPECT_TRUE(true);
}
TEST(OperationTests, CheckNormOneY) {
  yart::vector::Vector4 test = {0, 1, 0, 0};
  ASSERT_EQ(test.norm(), 1);
  EXPECT_TRUE(true);
}
TEST(OperationTests, CheckNormOneZ) {
  yart::vector::Vector4 test = {0, 0, 1, 0};
  ASSERT_EQ(test.norm(), 1);
  EXPECT_TRUE(true);
}
TEST(OperationTests, CheckNormOneW) {
  yart::vector::Vector4 test = {0, 0, 0, 1};
  ASSERT_EQ(test.norm(), 1);
  EXPECT_TRUE(true);
}

TEST(OperationTests, CheckNorm) {
  yart::vector::Vector4 test = {4, 3, 2, 1};
  float result = test.norm();
  float expected = std::sqrt(4 * 4 + 3 * 3 + 2 * 2 + 1);
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(OperationTests, CheckNormalized) {
  yart::vector::Vector4 test = {4, 3, 2, 1};
  auto result = test.normalized();
  float norm = test.norm();
  std::cout << result.norm();
  yart::vector::Vector4 expected = {4 / norm, 3 / norm, 2.0f / norm, 1.0f / norm};
  ASSERT_EQ(result, expected);
  ASSERT_TRUE(yart::math::approx_equals(result.norm(), 1.0f));
  EXPECT_TRUE(true);
}

TEST(OperationTests, CheckNormalizedZero) {
  auto result = yart::vector::Vector4::ZERO.normalized();
  ASSERT_EQ(result, yart::vector::Vector4::ZERO);
  EXPECT_TRUE(true);
}

TEST(OperationTests, CheckAbs) {
  yart::vector::Vector4 test = {-4, 3, 0, -2};
  auto result = test.abs();
  yart::vector::Vector4 expected = {4, 3, 0, 2};
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(OperationTests, CheckAbsZero) {
  yart::vector::Vector4 test = {0, 0, 0, 0};
  auto result = test.abs();
  ASSERT_EQ(result, yart::vector::Vector4::ZERO);
  EXPECT_TRUE(true);
}

TEST(OperationTests, CheckDot) {
  yart::vector::Vector4 test = {1, 2, 3, 4};
  yart::vector::Vector4 test2 = {2, 3, 4, 5};
  auto result = test.dot(test2);
  float expected = 1 * 2 + 2 * 3 + 3 * 4 + 4 * 5;
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

// TEST(OperationTests, CheckCross){
//   yart::vector::Vector4 test = {1, 2, 3};
//   yart::vector::Vector4 test2 = {2, 3, 4};

//   auto result = test.cross(test2);
//   auto expected = yart::vector::Vector4 {-1, 2, -1};

//   auto result2 = test2.cross(test);
//   auto expected2 = yart::vector::Vector4 {1, -2, 1};

//   ASSERT_EQ(result, expected);
//   ASSERT_EQ(result2, expected2);
//   EXPECT_TRUE(true);
// }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
