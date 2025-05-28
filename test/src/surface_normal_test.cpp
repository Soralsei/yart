#include <gtest/gtest.h>

#include <glm/geometric.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/io.hpp>
#include <memory>

#include "yart/geometry/primitives/plane.h"
#include "yart/geometry/primitives/sphere.h"
#include "yart/geometry/transform.h"

using namespace yart;

TEST(Normals, SphereNormalXAxis) {
  auto sphere = std::make_shared<geometry::Sphere>();
  auto normal = sphere->normal_at(glm::vec4{1, 0, 0, 1.0f});

  auto expected_normal = glm::vec4{1, 0, 0, 0};
  ASSERT_TRUE(glm::all(glm::epsilonEqual(normal, expected_normal, 1e-6f)))
      << "Expected " << expected_normal << ", got " << normal;
}

TEST(Normals, SphereNormalYAxis) {
  auto sphere = std::make_shared<geometry::Sphere>();
  auto normal = sphere->normal_at(glm::vec4{0, 1, 0, 1.0f});

  auto expected_normal = glm::vec4{0, 1, 0, 0};
  ASSERT_TRUE(glm::all(glm::epsilonEqual(normal, expected_normal, 1e-6f)))
      << "Expected " << expected_normal << ", got " << normal;
}

TEST(Normals, SphereNormalZAxis) {
  auto sphere = std::make_shared<geometry::Sphere>();
  auto normal = sphere->normal_at(glm::vec4{0, 0, 1, 1.0f});

  auto expected_normal = glm::vec4{0, 0, 1, 0};
  ASSERT_TRUE(glm::all(glm::epsilonEqual(normal, expected_normal, 1e-6f)))
      << "Expected " << expected_normal << ", got " << normal;
}

TEST(Normals, SphereNormalNonAxial) {
  auto sphere = std::make_shared<geometry::Sphere>();
  glm::vec4 normal
      = sphere->normal_at(glm::vec4{std::sqrt(3) / 3, std::sqrt(3) / 3, std::sqrt(3) / 3, 1.0f});

  glm::vec4 expected_normal
      = glm::vec4{std::sqrt(3.0f) / 3, std::sqrt(3.0f) / 3, std::sqrt(3.0f) / 3, 0};
  ASSERT_TRUE(glm::all(glm::epsilonEqual(normal, expected_normal, 1e-6f)))
      << "Expected " << expected_normal << ", got " << normal;
}

TEST(Normals, NormalIsNormalized) {
  auto sphere = std::make_shared<geometry::Sphere>();
  auto normal
      = sphere->normal_at(glm::vec4{std::sqrt(3) / 3, std::sqrt(3) / 3, std::sqrt(3) / 3, 0.0f});

  auto normalized_normal = glm::normalize(normal);
  ASSERT_TRUE(glm::all(glm::epsilonEqual(normal, normalized_normal, 1e-6f)));
}

TEST(Normals, SphereNormalTranslated) {
  auto transform = geometry::Transform{};
  transform.translate(0, 1, 0);
  auto sphere = std::make_shared<geometry::Sphere>(transform, 0.0f);
  auto normal = sphere->normal_at(glm::vec4{0, 1.70711f, -0.70711f, 1.0f});

  auto expected_normal = glm::vec4{0, 0.70711, -0.70711, 0};

  ASSERT_TRUE(glm::all(glm::epsilonEqual(normal, expected_normal, 1e-4f)))
      << "Expected " << expected_normal << ", got " << normal;
}

TEST(Normals, SphereNormalTransformed) {
  auto transform = geometry::Transform{};
  transform.scale(1, 0.5, 1).rotate_z(M_PI / 5);
  auto sphere = std::make_shared<geometry::Sphere>(transform, 0.0f);
  glm::vec4 normal = sphere->normal_at(glm::vec4{0, std::sqrt(2) / 2, -std::sqrt(2) / 2, 1.0f});

  glm::vec4 expected_normal = glm::vec4{0, 0.97014, -0.24254, 0};

  ASSERT_TRUE(glm::all(glm::epsilonEqual(normal, expected_normal, 1e-4f)))
      << "Expected " << expected_normal << ", got " << normal;
}

TEST(PlaneNormals, ConstantNormal) {
  geometry::Plane p;
  auto n1 = p.normal_at(glm::vec4{});
  auto n2 = p.normal_at({10, 0, -10, 1});
  auto n3 = p.normal_at({-5, 0, 150, 1});

  glm::vec4 expected_normal = glm::vec4{0, 1, 0, 0};

  ASSERT_TRUE(glm::all(glm::epsilonEqual(n1, expected_normal, 1e-4f)))
      << "Expected " << expected_normal << ", got " << n1;
  ASSERT_TRUE(glm::all(glm::epsilonEqual(n2, expected_normal, 1e-4f)))
      << "Expected " << expected_normal << ", got " << n2;
  ASSERT_TRUE(glm::all(glm::epsilonEqual(n3, expected_normal, 1e-4f)))
      << "Expected " << expected_normal << ", got " << n3;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}