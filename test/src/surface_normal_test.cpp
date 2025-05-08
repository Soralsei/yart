#include <gtest/gtest.h>

#include <memory>

#include "yart/geometry/intersection.h"
#include "yart/geometry/sphere.h"
#include "yart/geometry/transform.h"
#include "yart/util/vector.h"

using namespace yart;
using namespace Eigen;

TEST(Normals, SphereNormalXAxis) {
  auto sphere = std::make_shared<geometry::Sphere>();
  auto normal = sphere->normal_at(Vector3f(1, 0, 0));

  auto expected_normal = Vector3f(1, 0, 0);
  ASSERT_TRUE(normal.isApprox(expected_normal, 1e-6));
}

TEST(Normals, SphereNormalYAxis) {
  auto sphere = std::make_shared<geometry::Sphere>();
  auto normal = sphere->normal_at(Vector3f(0, 1, 0));

  auto expected_normal = Vector3f(0, 1, 0);
  ASSERT_TRUE(normal.isApprox(expected_normal, 1e-6));
}

TEST(Normals, SphereNormalZAxis) {
  auto sphere = std::make_shared<geometry::Sphere>();
  auto normal = sphere->normal_at(Vector3f(0, 0, 1));

  auto expected_normal = Vector3f(0, 0, 1);
  ASSERT_TRUE(normal.isApprox(expected_normal, 1e-6));
}

TEST(Normals, SphereNormalNonAxial) {
  auto sphere = std::make_shared<geometry::Sphere>();
  auto normal = sphere->normal_at(Vector3f(std::sqrt(3) / 3, std::sqrt(3) / 3, std::sqrt(3) / 3));

  auto expected_normal = Vector3f(std::sqrt(3) / 3, std::sqrt(3) / 3, std::sqrt(3) / 3);
  ASSERT_TRUE(normal.isApprox(expected_normal, 1e-6));
}

TEST(Normals, NormalIsNormalized) {
  auto sphere = std::make_shared<geometry::Sphere>();
  auto normal = sphere->normal_at(Vector3f(std::sqrt(3) / 3, std::sqrt(3) / 3, std::sqrt(3) / 3));

  auto normalized_normal = normal.normalized();
  ASSERT_TRUE(normal.isApprox(normalized_normal, 1e-6));
}

TEST(Normals, SphereNormalTranslated) {
  auto transform = geometry::Transform3d::Identity();
  transform.translate(Vector3f(0, 1, 0));
  auto sphere = std::make_shared<geometry::Sphere>(transform, 1.0f);
  auto normal = sphere->normal_at(Vector3f(0, 1.70711f, -0.70711f));
  
  auto expected_normal = Vector3f(0, 0.70711, -0.70711);
  std::cout << "Normal: " << normal.transpose() << "\n";
  std::cout << "Expected Normal: " << expected_normal.transpose() << "\n";

  ASSERT_TRUE(normal.isApprox(expected_normal, 1e-4));
}

TEST(Normals, SphereNormalTransformed) {
  auto transform = geometry::Transform3d::Identity();
  transform.scale(Vector3f(1, 0.5, 1)).rotate(transform::rotationZ<float>(M_PI / 5));
  auto sphere = std::make_shared<geometry::Sphere>(transform, 1.0f);
  auto normal = sphere->normal_at(Vector3f(0, std::sqrt(2)/2, -std::sqrt(2)/2));

  auto expected_normal = Vector3f(0, 0.97014, -0.24254);
  std::cout << "Normal: " << normal.transpose() << "\n";
  std::cout << "Expected Normal: " << expected_normal.transpose() << "\n";

  ASSERT_TRUE(normal.isApprox(expected_normal, 1e-4));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}