#include "yart/core/camera.h"

#include <gtest/gtest.h>

#include <iostream>

#include "Eigen/Dense"

using namespace yart;

TEST(ViewMatrix, Identity) {
  Eigen::Vector3f from{0, 0, 0};
  Eigen::Vector3f to{0, 0, 1};
  Eigen::Vector3f up{0, 1, 0};

  auto view = Camera::get_view_matrix(from, to, up);

  ASSERT_TRUE(view.isApprox(decltype(view)::Identity())) << "Expected Identity view matrix, got : " << view;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}