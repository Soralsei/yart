#include "yart/core/ray.h"

#include <gtest/gtest.h>

#include <memory>

#include "yart/geometry/intersection.h"
#include "yart/geometry/sphere.h"
#include "yart/geometry/transform.h"
#include "yart/util/vector.h"

using namespace Eigen;

TEST(Intersection, SphereIntersection1) {
  yart::Ray r = {Vector3f{0, 0, -5}, Vector3f{0, 0, 1}};
  auto s = std::make_shared<yart::geometry::Sphere>(1.0f);
  auto intersections = s->intersections(r);
  ASSERT_EQ(intersections.size(), 2);
  ASSERT_FLOAT_EQ(intersections[0].get_t(), 4.0f);
  ASSERT_FLOAT_EQ(intersections[1].get_t(), 6.0f);
}

TEST(Intersection, SphereIntersection2) {
  yart::Ray r = {Vector3f{0, 0, -5}, Vector3f{0, 0, 1}};
  auto s = std::make_shared<yart::geometry::Sphere>(2.0f);
  auto intersections = s->intersections(r);
  ASSERT_EQ(intersections.size(), 2);
  ASSERT_FLOAT_EQ(intersections[0].get_t(), 3.0f);
  ASSERT_FLOAT_EQ(intersections[1].get_t(), 7.0f);
}

TEST(Intersection, SphereTangent) {
  yart::Ray r = {Vector3f{0, 1, -5}, Vector3f{0, 0, 1}};
  auto s = std::make_shared<yart::geometry::Sphere>(1.0f);
  auto intersections = s->intersections(r);
  ASSERT_EQ(intersections.size(), 2);
  ASSERT_FLOAT_EQ(intersections[0].get_t(), 5.0f);
}

TEST(Intersection, SphereNoIntersection) {
  yart::Ray r = {Vector3f{0, 2, -5}, Vector3f{0, 0, 1}};
  auto s = std::make_shared<yart::geometry::Sphere>(1.0f);
  auto intersections = s->intersections(r);
  ASSERT_EQ(intersections.size(), 0);
}

TEST(Intersection, RayInsideSphere) {
  yart::Ray r = {Vector3f{0, 0, 0}, Vector3f{0, 0, 1}};
  auto s = std::make_shared<yart::geometry::Sphere>(1.0f);
  auto intersections = s->intersections(r);
  ASSERT_EQ(intersections.size(), 2);
  ASSERT_EQ(intersections[0].get_t(), -1);
  ASSERT_EQ(intersections[1].get_t(), 1);
}

TEST(Intersection, SphereBehindRay) {
  yart::Ray r = {Vector3f{0, 0, 5}, Vector3f{0, 0, 1}};
  auto s = std::make_shared<yart::geometry::Sphere>(1.0f);
  auto intersections = s->intersections(r);
  ASSERT_EQ(intersections.size(), 2);
  ASSERT_EQ(intersections[0].get_t(), -6);
  ASSERT_EQ(intersections[1].get_t(), -4);
}

TEST(Intersection, IntersectionInit) {
  auto s = std::make_shared<yart::geometry::Sphere>(1.0f);
  yart::geometry::Intersection i = {s, 3.5f};

  ASSERT_FLOAT_EQ(i.get_t(), 3.5f);
  ASSERT_EQ(i.get_object().lock(), s);
}

TEST(Intersection, MakeVecIntersection) {
  auto s = std::make_shared<yart::geometry::Sphere>(1.0f);
  yart::geometry::Intersection i1 = {s, 1};
  yart::geometry::Intersection i2 = {s, 2};
  auto intersections = yart::make_vec(i1, i2);

  ASSERT_EQ(intersections.size(), 2);
  ASSERT_FLOAT_EQ(intersections[0].get_t(), 1.0f);
  ASSERT_FLOAT_EQ(intersections[1].get_t(), 2.0f);
}

TEST(Intersection, HitTestPositive) {
  auto s = std::make_shared<yart::geometry::Sphere>(1.0f);
  yart::geometry::Intersection i1 = {s, 1};
  yart::geometry::Intersection i2 = {s, 2};
  auto intersections = yart::make_vec(i1, i2);

  auto hit = yart::geometry::hit(intersections);

  ASSERT_EQ((*hit), i1);
}

TEST(Intersection, HitTestNegative) {
  auto s = std::make_shared<yart::geometry::Sphere>(1.0f);
  yart::geometry::Intersection i1 = {s, -1};
  yart::geometry::Intersection i2 = {s, 1};
  auto intersections = yart::make_vec(i1, i2);

  auto hit = yart::geometry::hit(intersections);

  ASSERT_EQ((*hit), i2);
}

TEST(Intersection, HitTestAllNegative) {
  auto s = std::make_shared<yart::geometry::Sphere>(1.0f);
  yart::geometry::Intersection i1 = {s, -1};
  yart::geometry::Intersection i2 = {s, -2};
  auto intersections = yart::make_vec(i1, i2);

  auto hit = yart::geometry::hit(intersections);

  ASSERT_EQ(hit, nullptr);
}

TEST(Intersection, HitTest) {
  auto s = std::make_shared<yart::geometry::Sphere>(1.0f);
  yart::geometry::Intersection i1 = {s, 5};
  yart::geometry::Intersection i2 = {s, 7};
  yart::geometry::Intersection i3 = {s, -3};
  yart::geometry::Intersection i4 = {s, 2};
  auto intersections = yart::make_vec(i1, i2, i3, i4);

  auto hit = yart::geometry::hit(intersections);

  ASSERT_EQ((*hit), i4);
}

TEST(TransformRay, Translate) {
  yart::Ray r = {Vector3f{1, 2, 3}, Vector3f{0, 1, 0}};
  yart::geometry::Transform3D translation{yart::transform::translation<float>(3, 4, 5)};
  auto translated_ray = r.transform(translation);
  ASSERT_EQ(translated_ray.get_origin(), (Vector4f{4, 6, 8, 1}));
  ASSERT_EQ(translated_ray.get_direction(), (Vector4f{0, 1, 0, 0}));
}

TEST(TransformRay, Scaling) {
  yart::Ray r = {Vector3f{1, 2, 3}, Vector3f{0, 1, 0}};
  yart::geometry::Transform3D scale{yart::transform::scale<float>(2, 3, 4)};
  auto translated_ray = r.transform(scale);
  ASSERT_EQ(translated_ray.get_origin(), (Vector4f{2, 6, 12, 1}));
  ASSERT_EQ(translated_ray.get_direction(), (Vector4f{0, 3, 0, 0}));
}

TEST(TransformRay, IntersectionScaled) {
  yart::Ray r = {Vector3f{0, 0, -5}, Vector3f{0, 0, 1}};
  yart::geometry::Transform3D scale{yart::transform::scale<float>(2, 2, 2)};

  auto s = std::make_shared<yart::geometry::Sphere>(scale, 1);

  auto intersections = s->intersections(r);

  ASSERT_EQ(intersections.size(), 2);
  ASSERT_FLOAT_EQ(intersections[0].get_t(), 3.0f);
  ASSERT_FLOAT_EQ(intersections[1].get_t(), 7.0f);
}

TEST(TransformRay, IntersectionTranslated) {
  yart::Ray r = {Vector3f{0, 0, -5}, Vector3f{0, 0, 1}};
  yart::geometry::Transform3D scale{yart::transform::translation<float>(5, 0, 0)};

  auto s = std::make_shared<yart::geometry::Sphere>(scale, 1);

  auto intersections = s->intersections(r);
  ASSERT_EQ(intersections.size(), 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}