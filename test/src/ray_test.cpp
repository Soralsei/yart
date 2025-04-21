#include <gtest/gtest.h>
#include <memory>

#include "yart/math/ray.h"


#include "yart/geometry/sphere.h"
#include "yart/geometry/intersection.h"

using namespace Eigen;

TEST(Intersection, SphereIntersection1) {
  yart::Ray r = {Vector4f{0, 0, -5, 1}, Vector4f{0, 0, 1, 0}};
  yart::geometry::Sphere s = {1.0f};
  auto intersections = s.intersections(r);
  ASSERT_EQ(intersections.size(), 2);
  ASSERT_FLOAT_EQ(intersections[0], 4.0f);
  ASSERT_FLOAT_EQ(intersections[1], 6.0f);
}

TEST(Intersection, SphereIntersection2) {
  yart::Ray r = {Vector4f{0, 0, -5, 1}, Vector4f{0, 0, 1, 0}};
  yart::geometry::Sphere s = {2.0f};
  auto intersections = s.intersections(r);
  ASSERT_EQ(intersections.size(), 2);
  ASSERT_FLOAT_EQ(intersections[0], 3.0f);
  ASSERT_FLOAT_EQ(intersections[1], 7.0f);
}

TEST(Intersection, SphereTangent) {
  yart::Ray r = {Vector4f{0, 1, -5, 1}, Vector4f{0, 0, 1, 0}};
  yart::geometry::Sphere s = {1.0f};
  auto intersections = s.intersections(r);
  ASSERT_EQ(intersections.size(), 2);
  ASSERT_FLOAT_EQ(intersections[0], 5.0f);
}

TEST(Intersection, SphereNoIntersection) {
  yart::Ray r = {Vector4f{0, 2, -5, 1}, Vector4f{0, 0, 1, 0}};
  yart::geometry::Sphere s = {1.0f};
  auto intersections = s.intersections(r);
  ASSERT_EQ(intersections.size(), 0);
}

TEST(Intersection, RayInsideSphere) {
  yart::Ray r = {Vector4f{0, 0, 0, 1}, Vector4f{0, 0, 1, 0}};
  yart::geometry::Sphere s = {1.0f};
  auto intersections = s.intersections(r);
  ASSERT_EQ(intersections.size(), 2);
  ASSERT_EQ(intersections[0], -1);
  ASSERT_EQ(intersections[1], 1);
}

TEST(Intersection, SphereBehindRay) {
  yart::Ray r = {Vector4f{0, 0, 5, 1}, Vector4f{0, 0, 1, 0}};
  yart::geometry::Sphere s = {1.0f};
  auto intersections = s.intersections(r);
  ASSERT_EQ(intersections.size(), 2);
  ASSERT_EQ(intersections[0], -6);
  ASSERT_EQ(intersections[1], -4);
}

TEST(Intersection, IntersectionInit) {
  auto s = std::make_shared<yart::geometry::Sphere>(1.0f);
  yart::geometry::Intersection<yart::geometry::Sphere> i = {s, 3.5f};

  ASSERT_FLOAT_EQ(i.get_t(), 3.5f);
  ASSERT_EQ(i.get_object().lock(), s);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}