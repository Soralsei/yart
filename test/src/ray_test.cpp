#include <memory>

#include <gtest/gtest.h>

#include "yart/geometry/intersection.h"
#include "yart/geometry/sphere.h"
#include "yart/util/vector.h"
#include "yart/math/ray.h"

using namespace Eigen;

TEST(Intersection, SphereIntersection1) {
  yart::Ray r = {Vector4f{0, 0, -5, 1}, Vector4f{0, 0, 1, 0}};
  yart::geometry::Sphere s = {1.0f};
  auto intersections = s.intersections(r);
  ASSERT_EQ(intersections.size(), 2);
  ASSERT_FLOAT_EQ(intersections[0].get_t(), 4.0f);
  ASSERT_FLOAT_EQ(intersections[1].get_t(), 6.0f);
}

TEST(Intersection, SphereIntersection2) {
  yart::Ray r = {Vector4f{0, 0, -5, 1}, Vector4f{0, 0, 1, 0}};
  yart::geometry::Sphere s = {2.0f};
  auto intersections = s.intersections(r);
  ASSERT_EQ(intersections.size(), 2);
  ASSERT_FLOAT_EQ(intersections[0].get_t(), 3.0f);
  ASSERT_FLOAT_EQ(intersections[1].get_t(), 7.0f);
}

TEST(Intersection, SphereTangent) {
  yart::Ray r = {Vector4f{0, 1, -5, 1}, Vector4f{0, 0, 1, 0}};
  yart::geometry::Sphere s = {1.0f};
  auto intersections = s.intersections(r);
  ASSERT_EQ(intersections.size(), 2);
  ASSERT_FLOAT_EQ(intersections[0].get_t(), 5.0f);
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
  ASSERT_EQ(intersections[0].get_t(), -1);
  ASSERT_EQ(intersections[1].get_t(), 1);
}

TEST(Intersection, SphereBehindRay) {
  yart::Ray r = {Vector4f{0, 0, 5, 1}, Vector4f{0, 0, 1, 0}};
  yart::geometry::Sphere s = {1.0f};
  auto intersections = s.intersections(r);
  ASSERT_EQ(intersections.size(), 2);
  ASSERT_EQ(intersections[0].get_t(), -6);
  ASSERT_EQ(intersections[1].get_t(), -4);
}

TEST(Intersection, IntersectionInit) {
  auto s = std::make_shared<yart::geometry::Sphere>(1.0f);
  yart::geometry::Intersection<yart::geometry::Sphere> i = {s, 3.5f};

  ASSERT_FLOAT_EQ(i.get_t(), 3.5f);
  ASSERT_EQ(i.get_object().lock(), s);
}

TEST(Intersection, MakeVecIntersection) {
  auto s = std::make_shared<yart::geometry::Sphere>(1.0f);
  yart::geometry::Intersection<yart::geometry::Sphere> i1 = {s, 1};
  yart::geometry::Intersection<yart::geometry::Sphere> i2 = {s, 2};
  auto intersections = yart::make_vec(i1, i2);

  ASSERT_EQ(intersections.size(), 2);
  ASSERT_FLOAT_EQ(intersections[0].get_t(), 1.0f);
  ASSERT_FLOAT_EQ(intersections[1].get_t(), 2.0f);
}

TEST(Intersection, HitTestPositive) {
  auto s = std::make_shared<yart::geometry::Sphere>(1.0f);
  yart::geometry::Intersection<yart::geometry::Sphere> i1 = {s, 1};
  yart::geometry::Intersection<yart::geometry::Sphere> i2 = {s, 2};
  auto intersections = yart::make_vec(i1, i2);

  auto hit = yart::geometry::hit(intersections);
  
  ASSERT_EQ((*hit), i1);
}

TEST(Intersection, HitTestNegative) {
  auto s = std::make_shared<yart::geometry::Sphere>(1.0f);
  yart::geometry::Intersection<yart::geometry::Sphere> i1 = {s, -1};
  yart::geometry::Intersection<yart::geometry::Sphere> i2 = {s, 1};
  auto intersections = yart::make_vec(i1, i2);

  auto hit = yart::geometry::hit(intersections);
  
  ASSERT_EQ((*hit), i2);
}

TEST(Intersection, HitTestAllNegative) {
  auto s = std::make_shared<yart::geometry::Sphere>(1.0f);
  yart::geometry::Intersection<yart::geometry::Sphere> i1 = {s, -1};
  yart::geometry::Intersection<yart::geometry::Sphere> i2 = {s,-2};
  auto intersections = yart::make_vec(i1, i2);

  auto hit = yart::geometry::hit(intersections);
  
  ASSERT_EQ(hit, nullptr);
}

TEST(Intersection, HitTest) {
  auto s = std::make_shared<yart::geometry::Sphere>(1.0f);
  yart::geometry::Intersection<yart::geometry::Sphere> i1 = {s, 5};
  yart::geometry::Intersection<yart::geometry::Sphere> i2 = {s, 7};
  yart::geometry::Intersection<yart::geometry::Sphere> i3 = {s, -3};
  yart::geometry::Intersection<yart::geometry::Sphere> i4 = {s, 2};
  auto intersections = yart::make_vec(i1, i2, i3, i4);

  auto hit = yart::geometry::hit(intersections);
  
  ASSERT_EQ((*hit), i4);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}