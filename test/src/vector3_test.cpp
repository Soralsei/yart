#include "yart/math/vector3.h"

#include <gtest/gtest.h>

#include "yart/math/math.h"

TEST(InitTests, CheckCorrectInit) {
  yart::vector::Vector3 test = {1, 1, 1};
  ASSERT_EQ(test, yart::vector::ONE);
  EXPECT_TRUE(true);
}

TEST(EqualityTests, CheckEquals) {
  yart::vector::Vector3 test = {4, 3, 1};
  yart::vector::Vector3 test2 = {4, 3, 1};
  ASSERT_EQ(test, test2);
  EXPECT_TRUE(true);
}

TEST(EqualityTests, CheckNotEquals) {
  yart::vector::Vector3 test = {4, 3, 1};
  yart::vector::Vector3 test2 = {4, 3, 0};
  ASSERT_NE(test, test2);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckIncrement) {
  yart::vector::Vector3 test = {4, 3, 1};
  auto result = test + 1.0f;
  yart::vector::Vector3 expected = {5, 4, 2};
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}
TEST(ArithmeticTests, CheckSelfIncrement) {
  yart::vector::Vector3 test = {4, 3, 1};
  test += 1.0f;
  yart::vector::Vector3 expected = {5, 4, 2};
  ASSERT_EQ(test, expected);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckAddition) {
  yart::vector::Vector3 test = {4, 3, 1};
  auto result = test + yart::vector::ONE;
  yart::vector::Vector3 expected = {5, 4, 2};
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckSubtraction) {
  yart::vector::Vector3 test = {4, 3, 1};
  auto result = test - yart::vector::ONE;
  yart::vector::Vector3 expected = {3, 2, 0};
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckSubtractionZero) {
  yart::vector::Vector3 test = {4, 3, 1};
  auto result = test - yart::vector::ZERO;
  ASSERT_EQ(result, test);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckSubtractionSelf) {
  yart::vector::Vector3 test = {4, 3, 1};
  auto result = test - test;
  ASSERT_EQ(result, yart::vector::ZERO);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckMultiplicationOne) {
  yart::vector::Vector3 test = {4, 3, 1};
  auto result = test * yart::vector::ONE;
  ASSERT_EQ(result, test);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckDivisionOne) {
  yart::vector::Vector3 test = {4, 3, 1};
  auto result = test / yart::vector::ONE;
  ASSERT_EQ(result, test);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckSelfMult) {
  yart::vector::Vector3 test = {4, 3, 1};
  test *= yart::vector::Vector3{2, 0, 4};
  yart::vector::Vector3 expected = {8, 0, 4};
  ASSERT_EQ(test, expected);
  EXPECT_TRUE(true);
}

TEST(ArithmeticTests, CheckSelfDiv) {
  yart::vector::Vector3 test = {4, 3, 1};
  test /= yart::vector::Vector3{2, 1, 4};
  yart::vector::Vector3 expected = {2, 3, 1 / 4.0};
  ASSERT_EQ(test, expected);
  EXPECT_TRUE(true);
}

TEST(OperationTests, CheckNormOneX){
  yart::vector::Vector3 test = {1, 0, 0};
  ASSERT_EQ(test.norm(), 1);
  EXPECT_TRUE(true);
}
TEST(OperationTests, CheckNormOneY){
  yart::vector::Vector3 test = {0, 1, 0};
  ASSERT_EQ(test.norm(), 1);
  EXPECT_TRUE(true);
}
TEST(OperationTests, CheckNormOneZ){
  yart::vector::Vector3 test = {0, 0, 1};
  ASSERT_EQ(test.norm(), 1);
  EXPECT_TRUE(true);
}

TEST(OperationTests, CheckNorm){
  yart::vector::Vector3 test = {4, 3, 1};
  float result = test.norm();
  float expected = std::sqrt(4 * 4 + 3 * 3 + 1);
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(OperationTests, CheckNormalized){
  yart::vector::Vector3 test = {4, 3, 1};
  auto result = test.normalized();
  float norm = test.norm();
  yart::vector::Vector3 expected = {4 / norm, 3 / norm, 1 / norm};
  ASSERT_EQ(result, expected);
  ASSERT_EQ(result.norm(), 1);
  EXPECT_TRUE(true);
}

TEST(OperationTests, CheckNormalizedZero){
  auto result = yart::vector::ZERO.normalized();
  ASSERT_EQ(result, yart::vector::ZERO);
  EXPECT_TRUE(true);
}

TEST(OperationTests, CheckAbs){
  yart::vector::Vector3 test = {-4, 3, -1};
  auto result = test.abs();
  yart::vector::Vector3 expected = {4, 3, 1};
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(OperationTests, CheckAbsZero){
  yart::vector::Vector3 test = {0, 0, 0};
  auto result = test.abs();
  ASSERT_EQ(result, yart::vector::ZERO);
  EXPECT_TRUE(true);
}

TEST(OperationTests, CheckDot){
  yart::vector::Vector3 test = {1, 2, 3};
  yart::vector::Vector3 test2 = {2, 3, 4};
  auto result = test.dot(test2);
  float expected = 1 * 2 + 2 * 3 + 3 * 4;
  ASSERT_EQ(result, expected);
  EXPECT_TRUE(true);
}

TEST(OperationTests, CheckCross){
  yart::vector::Vector3 test = {1, 2, 3};
  yart::vector::Vector3 test2 = {2, 3, 4};

  auto result = test.cross(test2);
  auto expected = yart::vector::Vector3 {-1, 2, -1};

  auto result2 = test2.cross(test);
  auto expected2 = yart::vector::Vector3 {1, -2, 1};
  
  ASSERT_EQ(result, expected);
  ASSERT_EQ(result2, expected2);
  EXPECT_TRUE(true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
