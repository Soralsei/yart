#include "yart/core/world.hpp"

#include <gtest/gtest.h>

#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/io.hpp>

#include "yart/core/material.hpp"
#include "yart/core/ray.hpp"
#include "yart/geometry/hit.hpp"
#include "yart/geometry/primitives/sphere.hpp"
#include "yart/light/light.hpp"

using namespace yart;

TEST(Initialization, EmptyWorld) {
  World w{};
  ASSERT_TRUE(w.get_objects().empty());
  ASSERT_TRUE(w.get_light_sources().empty());
}

TEST(IntersectionsTests, DefaultWorld) {
  Ray ray{glm::vec3{0, 0, -5}, glm::vec3{0, 0, 1}};
  auto w = World::default_world();

  auto intersections = w->intersections(ray);

  ASSERT_EQ(intersections.size(), 4);

  ASSERT_FLOAT_EQ(intersections[0].get_t(), 4.0f);
  ASSERT_FLOAT_EQ(intersections[1].get_t(), 4.5f);
  ASSERT_FLOAT_EQ(intersections[2].get_t(), 5.5f);
  ASSERT_FLOAT_EQ(intersections[3].get_t(), 6.0f);
}

TEST(IntersectionsTests, PrecomputingIntersectionStates) {
  Ray ray{glm::vec3{0, 0, -5}, glm::vec3{0, 0, 1}};
  auto sphere = std::make_shared<geometry::Sphere>();
  auto intersection = geometry::Intersection(sphere, 4);
  auto hit = geometry::Hit::precompute_hit(ray, intersection);

  auto expected_pos = glm::vec4(0, 0, -1, 1);
  auto expected_eye = glm::vec4(0, 0, -1, 0);
  auto expected_normal = glm::vec4(0, 0, -1, 0);

  ASSERT_FLOAT_EQ(hit->get_t(), intersection.get_t());
  ASSERT_TRUE((*(hit->get_object().lock())) == (*(intersection.get_object().lock())))
      << "Hit and intersection objects are not equal\n";
  ASSERT_TRUE(glm::all(glm::epsilonEqual(hit->get_position(), expected_pos, 1e-6f)))
      << "Position vector for hit not correct, got : " << hit->get_position()
      << ", expected : " << expected_pos << "\n";
  ASSERT_TRUE(glm::all(glm::epsilonEqual(hit->get_eye(), expected_eye, 1e-6f)))
      << "Eye vector for hit not correct, got : " << hit->get_eye()
      << ", expected : " << expected_eye << "\n";
  ASSERT_TRUE(glm::all(glm::epsilonEqual(hit->get_normal(), expected_normal, 1e-6f)))
      << "Normal vector for hit not correct, got : " << hit->get_normal()
      << ", expected : " << expected_normal << "\n";
}

TEST(IntersectionsTests, HitOutside) {
  Ray ray{glm::vec3{0, 0, -5}, glm::vec3{0, 0, 1}};
  auto sphere = std::make_shared<geometry::Sphere>();
  auto intersection = geometry::Intersection(sphere, 4);

  auto hit = geometry::Hit::precompute_hit(ray, intersection);

  ASSERT_TRUE(!hit->is_inside());
}

TEST(IntersectionsTests, HitInside) {
  Ray ray{glm::vec3{0, 0, 0}, glm::vec3{0, 0, 1}};
  auto sphere = std::make_shared<geometry::Sphere>();
  auto intersection = geometry::Intersection(sphere, 1);

  auto hit = geometry::Hit::precompute_hit(ray, intersection);

  auto expected_pos = glm::vec4(0, 0, 1, 1);
  auto expected_eye = glm::vec4(0, 0, -1, 0);
  auto expected_normal = glm::vec4(0, 0, -1, 0);

  ASSERT_TRUE(hit->is_inside());

  ASSERT_TRUE((*(hit->get_object().lock())) == (*(intersection.get_object().lock())))
      << "Hit and intersection objects are not equal\n";
  ASSERT_TRUE(glm::all(glm::epsilonEqual(hit->get_position(), expected_pos, 1e-6f)))
      << "Position vector for hit not correct, got : " << hit->get_position()
      << ", expected : " << expected_pos << "\n";
  ASSERT_TRUE(glm::all(glm::epsilonEqual(hit->get_eye(), expected_eye, 1e-6f)))
      << "Eye vector for hit not correct, got : " << hit->get_eye()
      << ", expected : " << expected_eye << "\n";
  ASSERT_TRUE(glm::all(glm::epsilonEqual(hit->get_normal(), expected_normal, 1e-6f)))
      << "Normal vector for hit not correct, got : " << hit->get_normal()
      << ", expected : " << expected_normal << "\n";
}

TEST(IntersectionsTests, ShadingHit) {
  auto world = World::default_world();
  Ray ray{glm::vec3{0, 0, -5}, glm::vec3{0, 0, 1}};
  auto shape = world->get_objects()[0];
  auto intersection = geometry::Intersection(shape, 4);

  auto hit = geometry::Hit::precompute_hit(ray, intersection);

  color::Color shade = light::shade_hit(*world, *hit);
  color::Color expected{0.38066, 0.47583, 0.2855};

  ASSERT_EQ(shade, expected);
}

TEST(IntersectionsTests, ColorAtMiss) {
  auto world = World::default_world();
  Ray ray{glm::vec3{0, 0, -5}, glm::vec3{0, 1, 0}};

  color::Color shade = world->color_at(ray);
  color::Color expected = color::Black;

  ASSERT_EQ(shade, expected);
}

TEST(IntersectionsTests, ColorAtHit) {
  auto world = World::default_world();
  Ray ray{glm::vec3{0, 0, -5}, glm::vec3{0, 0, 1}};

  color::Color shade = world->color_at(ray);
  color::Color expected{0.38066, 0.47583, 0.2855};

  ASSERT_EQ(shade, expected);
}

TEST(IntersectionsTests, ColorAtHitBehind) {
  auto world = World::default_world();
  Ray ray{glm::vec3{0, 0, 0.75}, glm::vec3{0, 0, -1}};
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