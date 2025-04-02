#include "yart/math/vector2.h"

#include <gtest/gtest.h>


TEST(InitTests, CheckCorrectInit) {
  yart::vector::Vector2 test = {1, 1};
  ASSERT_EQ(test, yart::vector::Vector2::ONE);
  EXPECT_TRUE(true);
}

TEST(EqualityTests, CheckEquals) {
  yart::vector::Vector2 test = {4, 3};
  yart::vector::Vector2 test2 = {4, 3};
  ASSERT_EQ(test, test2);
  EXPECT_TRUE(true);
}

TEST(EqualityTests, CheckNotEquals) {
  yart::vector::Vector2 test = {4, 3};
  yart::vector::Vector2 test2 = {4, 2};
  ASSERT_NE(test, test2);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckIncrement) {
  yart::vector::Vector2 test = {4, 3};
  auto result = test + 1.0f;
  yart::vector::Vector2 expected = {5, 4};
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}
TEST(ArithmeticTests, CheckSelfIncrement) {
  yart::vector::Vector2 test = {4, 3};
  test += 1.0f;
  yart::vector::Vector2 expected = {5, 4};
  ASSERT_EQ(test, expected);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckAddition) {
  yart::vector::Vector2 test = {4, 3};
  auto result = test + yart::vector::Vector2::ONE;
  yart::vector::Vector2 expected = {5, 4};
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckSubtraction) {
  yart::vector::Vector2 test = {4, 3};
  auto result = test - yart::vector::Vector2::ONE;
  yart::vector::Vector2 expected = {3, 2};
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckSubtractionZero) {
  yart::vector::Vector2 test = {4, 3};
  auto result = test - yart::vector::Vector2::ZERO;
  ASSERT_EQ(result, test);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckSubtractionSelf) {
  yart::vector::Vector2 test = {4, 3};
  auto result = test - test;
  ASSERT_EQ(result, yart::vector::Vector2::ZERO);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckMultiplicationOne) {
  yart::vector::Vector2 test = {4, 3};
  auto result = test * yart::vector::Vector2::ONE;
  ASSERT_EQ(result, test);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckDivisionOne) {
  yart::vector::Vector2 test = {4, 3};
  auto result = test / yart::vector::Vector2::ONE;
  ASSERT_EQ(result, test);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckSelfMult) {
  yart::vector::Vector2 test = {4, 3};
  test *= yart::vector::Vector2{2, 0};
  yart::vector::Vector2 expected = {8, 0};
  ASSERT_EQ(test, expected);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckSelfDiv) {
  yart::vector::Vector2 test = {4, 3};
  test /= yart::vector::Vector2{2, 1};
  yart::vector::Vector2 expected = {2, 3};
  ASSERT_EQ(test, expected);
  EXPECT_TRUE(true);
}

TEST(OperationTests, CheckNormOneX){
  yart::vector::Vector2 test = {1, 0};
  ASSERT_EQ(test.norm(), 1);
  EXPECT_TRUE(true);
}
TEST(OperationTests, CheckNormOneY){
  yart::vector::Vector2 test = {0, 1};
  ASSERT_EQ(test.norm(), 1);
  EXPECT_TRUE(true);
}

TEST(OperationTests, CheckNorm){
  yart::vector::Vector2 test = {4, 3};
  float result = test.norm();
  float expected = std::sqrt(4 * 4 + 3 * 3);
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(OperationTests, CheckNormalized){
  yart::vector::Vector2 test = {4, 3};
  auto result = test.normalized();
  float norm = test.norm();
  yart::vector::Vector2 expected = {4 / norm, 3 / norm};
  ASSERT_EQ(result, expected);
  ASSERT_EQ(result.norm(), 1);
  EXPECT_TRUE(true);
}

TEST(OperationTests, CheckNormalizedZero){
  auto result = yart::vector::Vector2::ZERO.normalized();
  ASSERT_EQ(result, yart::vector::Vector2::ZERO);
  EXPECT_TRUE(true);
}

TEST(OperationTests, CheckAbs){
  yart::vector::Vector2 test = {-4, 3};
  auto result = test.abs();
  yart::vector::Vector2 expected = {4, 3};
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(OperationTests, CheckAbsZero){
  yart::vector::Vector2 test = {0, 0};
  auto result = test.abs();
  ASSERT_EQ(result, yart::vector::Vector2::ZERO);
  EXPECT_TRUE(true);
}

TEST(OperationTests, CheckDot){
  yart::vector::Vector2 test = {1, 2};
  yart::vector::Vector2 test2 = {2, 3};
  auto result = test.dot(test2);
  float expected = 1 * 2 + 2 * 3;
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

// TEST(OperationTests, CheckCross){
//   yart::vector::Vector2 test = {1, 2, 3};
//   yart::vector::Vector2 test2 = {2, 3, 4};

//   auto result = test.cross(test2);
//   auto expected = yart::vector::Vector2 {-1, 2, -1};

//   auto result2 = test2.cross(test);
//   auto expected2 = yart::vector::Vector2 {1, -2, 1};
  
//   ASSERT_EQ(result, expected);
//   ASSERT_EQ(result2, expected2);
//   EXPECT_TRUE(true);
// }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
