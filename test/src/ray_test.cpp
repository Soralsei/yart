#include "yart/core/ray.hpp"

#include <gtest/gtest.h>

#include <glm/gtx/io.hpp>
#include <memory>
#include <optional>

#include "yart/geometry/intersection.hpp"
#include "yart/geometry/primitives/plane.hpp"
#include "yart/geometry/primitives/sphere.hpp"
#include "yart/util/vector.hpp"

using namespace yart;

TEST(Intersection, SphereIntersection1) {
  Ray r = {glm::vec3{0, 0, -5}, glm::vec3{0, 0, 1}};
  auto s = std::make_shared<geometry::Sphere>(1.0f);
  auto intersections = s->intersections(r);
  ASSERT_EQ(intersections.size(), 2);
  ASSERT_FLOAT_EQ(intersections[0].get_t(), 4.0f);
  ASSERT_FLOAT_EQ(intersections[1].get_t(), 6.0f);
}

TEST(Intersection, SphereIntersection2) {
  Ray r = {glm::vec3{0, 0, -5}, glm::vec3{0, 0, 1}};
  auto s = std::make_shared<geometry::Sphere>(2.0f);
  auto intersections = s->intersections(r);
  ASSERT_EQ(intersections.size(), 2);
  ASSERT_FLOAT_EQ(intersections[0].get_t(), 3.0f);
  ASSERT_FLOAT_EQ(intersections[1].get_t(), 7.0f);
}

TEST(Intersection, SphereTangent) {
  Ray r = {glm::vec3{0, 1, -5}, glm::vec3{0, 0, 1}};
  auto s = std::make_shared<geometry::Sphere>(1.0f);
  auto intersections = s->intersections(r);
  ASSERT_EQ(intersections.size(), 2);
  ASSERT_FLOAT_EQ(intersections[0].get_t(), 5.0f);
}

TEST(Intersection, SphereNoIntersection) {
  Ray r = {glm::vec3{0, 2, -5}, glm::vec3{0, 0, 1}};
  auto s = std::make_shared<geometry::Sphere>(1.0f);
  auto intersections = s->intersections(r);
  ASSERT_EQ(intersections.size(), 0);
}

TEST(Intersection, RayInsideSphere) {
  Ray r = {glm::vec3{0, 0, 0}, glm::vec3{0, 0, 1}};
  auto s = std::make_shared<geometry::Sphere>(1.0f);
  auto intersections = s->intersections(r);
  ASSERT_EQ(intersections.size(), 2);
  ASSERT_EQ(intersections[0].get_t(), -1);
  ASSERT_EQ(intersections[1].get_t(), 1);
}

TEST(Intersection, SphereBehindRay) {
  Ray r = {glm::vec3{0, 0, 5}, glm::vec3{0, 0, 1}};
  auto s = std::make_shared<geometry::Sphere>(1.0f);
  auto intersections = s->intersections(r);
  ASSERT_EQ(intersections.size(), 2);
  ASSERT_EQ(intersections[0].get_t(), -6);
  ASSERT_EQ(intersections[1].get_t(), -4);
}

TEST(Intersection, IntersectionInit) {
  auto s = std::make_shared<geometry::Sphere>(1.0f);
  geometry::Intersection i = {s, 3.5f};

  ASSERT_FLOAT_EQ(i.get_t(), 3.5f);
  ASSERT_EQ(i.get_object().lock(), s);
}

TEST(Intersection, MakeVecIntersection) {
  auto s = std::make_shared<geometry::Sphere>(1.0f);
  geometry::Intersection i1 = {s, 1};
  geometry::Intersection i2 = {s, 2};
  auto intersections = make_vec(i1, i2);

  ASSERT_EQ(intersections.size(), 2);
  ASSERT_FLOAT_EQ(intersections[0].get_t(), 1.0f);
  ASSERT_FLOAT_EQ(intersections[1].get_t(), 2.0f);
}

TEST(Intersection, HitTestPositive) {
  auto s = std::make_shared<geometry::Sphere>(1.0f);
  geometry::Intersection i1 = {s, 1};
  geometry::Intersection i2 = {s, 2};
  auto intersections = make_vec(i1, i2);

  auto hit = geometry::hit(intersections);

  ASSERT_EQ(hit.value(), i1);
}

TEST(Intersection, HitTestNegative) {
  auto s = std::make_shared<geometry::Sphere>(1.0f);
  geometry::Intersection i1 = {s, -1};
  geometry::Intersection i2 = {s, 1};
  auto intersections = make_vec(i1, i2);

  auto hit = geometry::hit(intersections);

  ASSERT_EQ(hit.value(), i2);
}

TEST(Intersection, HitTestAllNegative) {
  auto s = std::make_shared<geometry::Sphere>(1.0f);
  geometry::Intersection i1 = {s, -1};
  geometry::Intersection i2 = {s, -2};
  auto intersections = make_vec(i1, i2);

  auto hit = geometry::hit(intersections);

  ASSERT_EQ(hit, std::nullopt);
}

TEST(Intersection, HitTest) {
  auto s = std::make_shared<geometry::Sphere>(1.0f);
  geometry::Intersection i1 = {s, 5};
  geometry::Intersection i2 = {s, 7};
  geometry::Intersection i3 = {s, -3};
  geometry::Intersection i4 = {s, 2};
  auto intersections = make_vec(i1, i2, i3, i4);

  auto hit = geometry::hit(intersections);

  ASSERT_EQ(hit.value(), i4);
}

TEST(TransformRay, Translate) {
  Ray r = {glm::vec3{1, 2, 3}, glm::vec3{0, 1, 0}};
  geometry::Transform translation{};
  std::cout << "Translation matrix:\n" << translation.matrix() << "\n";
  translation.translate(glm::vec3{3, 4, 5});
  auto translated_ray = r.transform(translation);
  ASSERT_EQ(translated_ray.get_origin(), (glm::vec4{4, 6, 8, 1}));
  ASSERT_EQ(translated_ray.get_direction(), (glm::vec4{0, 1, 0, 0}));
}

TEST(TransformRay, Scaling) {
  Ray r = {glm::vec3{1, 2, 3}, glm::vec3{0, 1, 0}};
  geometry::Transform scale{};
  scale.scale(glm::vec3{2, 3, 4});
  auto translated_ray = r.transform(scale);
  ASSERT_EQ(translated_ray.get_origin(), (glm::vec4{2, 6, 12, 1}));
  ASSERT_EQ(translated_ray.get_direction(), (glm::vec4{0, 3, 0, 0}));
}

TEST(TransformRay, IntersectionScaled) {
  Ray r = {glm::vec3{0, 0, -5}, glm::vec3{0, 0, 1}};
  geometry::Transform scale{};
  scale.scale(glm::vec3{2, 2, 2});

  auto s = std::make_shared<geometry::Sphere>(scale, 1);

  auto intersections = s->intersections(r);

  ASSERT_EQ(intersections.size(), 2);
  ASSERT_FLOAT_EQ(intersections[0].get_t(), 3.0f);
  ASSERT_FLOAT_EQ(intersections[1].get_t(), 7.0f);
}

TEST(TransformRay, IntersectionTranslated) {
  Ray r = {glm::vec3{0, 0, -5}, glm::vec3{0, 0, 1}};
  geometry::Transform translation{};
  translation.translate(glm::vec3{5, 0, 0});

  auto s = std::make_shared<geometry::Sphere>(translation, 1);

  auto intersections = s->intersections(r);
  ASSERT_EQ(intersections.size(), 0);
}

TEST(PlaneNormals, RayParallel) {
  geometry::Plane p;
  Ray r{glm::vec3{0, 10, 0}, glm::vec3{0, 0, 1}};
  auto i = p.intersections(r);

  ASSERT_TRUE(i.empty());
}

TEST(PlaneNormals, RayCoplanar) {
  geometry::Plane p;
  Ray r{glm::vec3{0, 0, 0}, glm::vec3{0, 0, 1}};
  auto i = p.intersections(r);

  ASSERT_TRUE(i.empty());
}

TEST(PlaneNormals, RayFromAbove) {
  std::shared_ptr<geometry::Plane> p = std::make_shared<geometry::Plane>();
  Ray r{glm::vec3{0, 1, 0}, glm::vec3{0, -1, 0}};
  auto i = p->intersections(r);

  ASSERT_EQ(i.size(), 1);
  ASSERT_FLOAT_EQ(i[0].get_t(), 1);
  ASSERT_EQ(*i[0].get_object().lock(), *p);
}

TEST(PlaneNormals, RayFromBelow) {
  std::shared_ptr<geometry::Plane> p = std::make_shared<geometry::Plane>();
  Ray r{glm::vec3{0, -1, 0}, glm::vec3{0, 1, 0}};
  auto i = p->intersections(r);

  ASSERT_EQ(i.size(), 1);
  ASSERT_FLOAT_EQ(i[0].get_t(), 1);
  ASSERT_EQ(*i[0].get_object().lock(), *p);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}