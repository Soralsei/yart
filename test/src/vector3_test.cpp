#include "yart/math/vector3.h"

#include <gtest/gtest.h>

TEST(Vector3InitTest, CheckCorrectInit) {
  yart::vector::Vector3 test = {1, 1, 1};
  ASSERT_EQ(test, yart::vector::ONE);
  EXPECT_TRUE(true);
}

TEST(Vector3InitTest, CheckEquals) {
  yart::vector::Vector3 test = {4, 3, 1};
  yart::vector::Vector3 test2 = {4, 3, 1};
  ASSERT_EQ(test, test2);
  EXPECT_TRUE(true);
}
TEST(Vector3InitTest, CheckNotEquals) {
  yart::vector::Vector3 test = {4, 3, 1};
  yart::vector::Vector3 test2 = {4, 3, 0};
  ASSERT_NE(test, test2);
  EXPECT_TRUE(true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
