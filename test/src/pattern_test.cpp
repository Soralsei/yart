#include <gtest/gtest.h>

#include <glm/ext/vector_float4.hpp>

#include "yart/image/color.hpp"

using namespace yart;

class StripePatternTest : public testing::Test {
protected:
  StripePatternTest() {}

  color::Color black = color::Black;
  color::Color white = color::White;
  StripePattern p{white, black};
};

TEST_F(StripePatternTest, Initialization) {
  ASSERT_EQ(p.a, white);
  ASSERT_EQ(p.b, black);
}

TEST_F(StripePatternTest, ConstantY) {
  ASSERT_EQ(p.stripe_at(glm::vec4{0, 0, 0, 1}), white);
  ASSERT_EQ(p.stripe_at(glm::vec4{0, 1, 0, 1}), white);
  ASSERT_EQ(p.stripe_at(glm::vec4{0, 2, 0, 1}), white);
}

TEST_F(StripePatternTest, ConstantZ) {
  ASSERT_EQ(p.stripe_at(glm::vec4{0, 0, 0, 1}), white);
  ASSERT_EQ(p.stripe_at(glm::vec4{0, 0, 1, 1}), white);
  ASSERT_EQ(p.stripe_at(glm::vec4{0, 0, 2, 1}), white);
}

TEST_F(StripePatternTest, AlternatesX) {
  ASSERT_EQ(p.stripe_at(glm::vec4{0, 0, 0, 1}), white);
  ASSERT_EQ(p.stripe_at(glm::vec4{0.9f, 0, 0, 1}), white);

  ASSERT_EQ(p.stripe_at(glm::vec4{1, 0, 0, 1}), black);
  ASSERT_EQ(p.stripe_at(glm::vec4{-0.1f, 0, 0, 1}), black);
  ASSERT_EQ(p.stripe_at(glm::vec4{-1, 0, 0, 1}), black);

  ASSERT_EQ(p.stripe_at(glm::vec4{-1.1f, 0, 0, 1}), white);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}