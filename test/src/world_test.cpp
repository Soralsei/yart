#include "yart/core/world.h"

#include <gtest/gtest.h>

#include "yart/core/material.h"
#include "yart/core/ray.h"
#include "yart/geometry/hit.h"
#include "yart/geometry/sphere.h"
#include "yart/geometry/transform.h"
#include "yart/light/light.h"
#include "yart/light/point_light.h"

using namespace yart;

TEST(Initialization, EmptyWorld) {
  World w{};
  ASSERT_TRUE(w.get_objects().empty());
  ASSERT_TRUE(w.get_light_sources().empty());
}

TEST(IntersectionsTests, DefaultWorld) {
  Ray ray{Eigen::Vector3f{0, 0, -5}, Eigen::Vector3f{0, 0, 1}};
  auto w = World::default_world();

  auto intersections = w->intersections(ray);

  ASSERT_EQ(intersections.size(), 4);

  ASSERT_FLOAT_EQ(intersections[0].get_t(), 4.0f);
  ASSERT_FLOAT_EQ(intersections[1].get_t(), 4.5f);
  ASSERT_FLOAT_EQ(intersections[2].get_t(), 5.5f);
  ASSERT_FLOAT_EQ(intersections[3].get_t(), 6.0f);
}

TEST(IntersectionsTests, PrecomputingIntersectionStates) {
  Ray ray{Eigen::Vector3f{0, 0, -5}, Eigen::Vector3f{0, 0, 1}};
  auto sphere = std::make_shared<geometry::Sphere>();
  auto intersection = geometry::Intersection(sphere, 4);
  auto hit = geometry::Hit::precompute_hit(ray, intersection);

  auto expected_pos = Eigen::Vector4f(0, 0, -1, 1);
  auto expected_eye = Eigen::Vector4f(0, 0, -1, 0);
  auto expected_normal = Eigen::Vector4f(0, 0, -1, 0);

  ASSERT_FLOAT_EQ(hit->get_t(), intersection.get_t());
  ASSERT_TRUE((*(hit->get_object().lock())) == (*(intersection.get_object().lock())))
      << "Hit and intersection objects are not equal\n";
  ASSERT_TRUE(hit->get_position().isApprox(expected_pos))
      << "Position vector for hit not correct, got : " << hit->get_position().transpose()
      << ", expected : " << expected_pos.transpose() << "\n";
  ASSERT_TRUE(hit->get_eye().isApprox(expected_eye))
      << "Eye vector for hit not correct, got : " << hit->get_eye().transpose()
      << ", expected : " << expected_eye.transpose() << "\n";
  ASSERT_TRUE(hit->get_normal().isApprox(expected_normal))
      << "Normal vector for hit not correct, got : " << hit->get_normal().transpose()
      << ", expected : " << expected_normal.transpose() << "\n";
}

TEST(IntersectionsTests, HitOutside) {
  Ray ray{Eigen::Vector3f{0, 0, -5}, Eigen::Vector3f{0, 0, 1}};
  auto sphere = std::make_shared<geometry::Sphere>();
  auto intersection = geometry::Intersection(sphere, 4);

  auto hit = geometry::Hit::precompute_hit(ray, intersection);

  ASSERT_TRUE(!hit->is_inside());
}

TEST(IntersectionsTests, HitInside) {
  Ray ray{Eigen::Vector3f{0, 0, 0}, Eigen::Vector3f{0, 0, 1}};
  auto sphere = std::make_shared<geometry::Sphere>();
  auto intersection = geometry::Intersection(sphere, 1);

  auto hit = geometry::Hit::precompute_hit(ray, intersection);

  auto expected_pos = Eigen::Vector4f(0, 0, 1, 1);
  auto expected_eye = Eigen::Vector4f(0, 0, -1, 0);
  auto expected_normal = Eigen::Vector4f(0, 0, -1, 0);

  ASSERT_TRUE(hit->is_inside());

  ASSERT_TRUE((*(hit->get_object().lock())) == (*(intersection.get_object().lock())))
      << "Hit and intersection objects are not equal\n";
  ASSERT_TRUE(hit->get_position().isApprox(expected_pos))
      << "Position vector for hit not correct, got : " << hit->get_position().transpose()
      << ", expected : " << expected_pos.transpose() << "\n";
  ASSERT_TRUE(hit->get_eye().isApprox(expected_eye))
      << "Eye vector for hit not correct, got : " << hit->get_eye().transpose()
      << ", expected : " << expected_eye.transpose() << "\n";
  ASSERT_TRUE(hit->get_normal().isApprox(expected_normal))
      << "Normal vector for hit not correct, got : " << hit->get_normal().transpose()
      << ", expected : " << expected_normal.transpose() << "\n";
}

TEST(IntersectionsTests, ShadingHit) {
  auto world = World::default_world();
  Ray ray{Eigen::Vector3f{0, 0, -5}, Eigen::Vector3f{0, 0, 1}};
  auto shape = world->get_objects()[0];
  auto intersection = geometry::Intersection(shape, 4);

  auto hit = geometry::Hit::precompute_hit(ray, intersection);

  color::Color shade = light::shade_hit(*world, *hit);
  color::Color expected{0.38066, 0.47583, 0.2855};

  ASSERT_EQ(shade, expected);
}

TEST(IntersectionsTests, ColorAtMiss) {
  auto world = World::default_world();
  Ray ray{Eigen::Vector3f{0, 0, -5}, Eigen::Vector3f{0, 1, 0}};

  color::Color shade = world->color_at(ray);
  color::Color expected = color::Black;

  ASSERT_EQ(shade, expected);
}

TEST(IntersectionsTests, ColorAtHit) {
  auto world = World::default_world();
  Ray ray{Eigen::Vector3f{0, 0, -5}, Eigen::Vector3f{0, 0, 1}};

  color::Color shade = world->color_at(ray);
  color::Color expected{0.38066, 0.47583, 0.2855};

  ASSERT_EQ(shade, expected);
}

TEST(IntersectionsTests, ColorAtHitBehind) {
  auto world = World::default_world();
  Ray ray{Eigen::Vector3f{0, 0, 0.75}, Eigen::Vector3f{0, 0, -1}};
  auto outer = world->get_objects()[0];
  outer->get_material().set_ambient(1);
  auto inner = world->get_objects()[1];
  inner->get_material().set_ambient(1);

  color::Color shade = world->color_at(ray);
  color::Color expected = inner->get_material().get_diffuse_color();

  ASSERT_EQ(shade, expected);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}