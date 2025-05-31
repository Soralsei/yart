#include <gtest/gtest.h>

#include "yart/core/material.hpp"
#include "yart/core/world.hpp"
#include "yart/geometry/primitives/sphere.hpp"
#include "yart/light/light.hpp"
#include "yart/light/point_light.hpp"

using namespace yart;

class ShadingTest : public testing::Test {
protected:
  ShadingTest() { position = glm::vec4{0, 0, 0, 1}; }

  Material material;
  glm::vec4 position;
};

TEST(MaterialTest, DefaultConstructor) {
  Material material;
  EXPECT_FLOAT_EQ(material.get_ambient(), 0.1f);
  EXPECT_FLOAT_EQ(material.get_diffuse(), 0.9f);
  EXPECT_FLOAT_EQ(material.get_specular(), 0.9f);
  EXPECT_FLOAT_EQ(material.get_shininess(), 200.0f);
}

TEST(MaterialTest, ShapeHasDefaultMaterial) {
  geometry::Sphere sphere;
  EXPECT_FLOAT_EQ(sphere.get_material().get_ambient(), 0.1f);
  EXPECT_FLOAT_EQ(sphere.get_material().get_diffuse(), 0.9f);
  EXPECT_FLOAT_EQ(sphere.get_material().get_specular(), 0.9f);
  EXPECT_FLOAT_EQ(sphere.get_material().get_shininess(), 200.0f);
}

TEST(MaterialTest, MaterialAssign) {
  geometry::Sphere sphere;

  EXPECT_FLOAT_EQ(sphere.get_material().get_ambient(), 0.1f);
  EXPECT_FLOAT_EQ(sphere.get_material().get_diffuse(), 0.9f);
  EXPECT_FLOAT_EQ(sphere.get_material().get_specular(), 0.9f);
  EXPECT_FLOAT_EQ(sphere.get_material().get_shininess(), 200.0f);

  Material material;
  material.set_ambient(1);
  sphere.get_material() = material;

  EXPECT_FLOAT_EQ(sphere.get_material().get_ambient(), 1.0f);
  EXPECT_FLOAT_EQ(sphere.get_material().get_diffuse(), 0.9f);
  EXPECT_FLOAT_EQ(sphere.get_material().get_specular(), 0.9f);
  EXPECT_FLOAT_EQ(sphere.get_material().get_shininess(), 200.0f);
}

TEST_F(ShadingTest, EyeBetweenLightAndSurface) {
  auto eye = glm::vec4{0, 0, -1, 0};
  auto normal = glm::vec4{0, 0, -1, 0};
  light::PointLight light{glm::vec3{0, 0, -10}};

  auto result = light::phong_lighting(material, light, position, eye, normal);
  ASSERT_EQ(result, (color::Color{1.9f, 1.9f, 1.9f}));
}

TEST_F(ShadingTest, EyeOffset45Degrees) {
  auto eye = glm::vec4{0, std::sqrt(2.0f) / 2, -std::sqrt(2.0f) / 2, 0};
  auto normal = glm::vec4{0, 0, -1, 0};
  light::PointLight light{glm::vec3{0, 0, -10}};

  auto result = light::phong_lighting(material, light, position, eye, normal);
  ASSERT_EQ(result, (color::Color{1.0f, 1.0f, 1.0f}));
}

TEST_F(ShadingTest, LightOffset45Degrees) {
  auto eye = glm::vec4{0, 0, -1, 0};
  auto normal = glm::vec4{0, 0, -1, 0};
  light::PointLight light{glm::vec3{0, 10, -10}};

  auto result = light::phong_lighting(material, light, position, eye, normal);
  ASSERT_EQ(result, (color::Color{0.7364f, 0.7364f, 0.7364f}));
}

TEST_F(ShadingTest, LightAndEyeOffset45Degrees) {
  auto eye = glm::vec4{0, -std::sqrt(2.0f) / 2, -std::sqrt(2.0f) / 2, 0};
  auto normal = glm::vec4{0, 0, -1, 0};
  light::PointLight light{glm::vec3{0, 10, -10}};

  auto result = light::phong_lighting(material, light, position, eye, normal);
  ASSERT_EQ(result, (color::Color{1.6364, 1.6364, 1.6364}));
}
TEST_F(ShadingTest, LightBehindSurface) {
  auto eye = glm::vec4{0, 0, -1, 0};
  auto normal = glm::vec4{0, 0, -1, 0};
  light::PointLight light{glm::vec3{0, 0, 10}};

  auto result = light::phong_lighting(material, light, position, eye, normal);
  ASSERT_EQ(result, (color::Color{0.1, 0.1, 0.1}));
}
TEST_F(ShadingTest, LightShadowedSurface) {
  auto eye = glm::vec4{0, 0, -1, 0};
  auto normal = glm::vec4{0, 0, -1, 0};
  light::PointLight light{glm::vec3{0, 0, 10}};

  auto result = light::phong_lighting(material, light, position, eye, normal, true);
  ASSERT_EQ(result, (color::Color{0.1, 0.1, 0.1}));
}

TEST(ShadowTests, NotShadowed) {
  auto w = World::default_world();
  glm::vec4 p{0, 10, 0, 1};
  for (auto&& light : w->get_light_sources()) {
    ASSERT_FALSE(light::is_shadowed(*w, *light, p));
  }
}

TEST(ShadowTests, ObjectBetweenLightAndPoint) {
  auto w = World::default_world();
  glm::vec4 p{10, -10, 10, 1};
  for (auto&& light : w->get_light_sources()) {
    ASSERT_TRUE(light::is_shadowed(*w, *light, p));
  }
}

TEST(ShadowTests, LightBetweenObjectAndPoint) {
  auto w = World::default_world();
  glm::vec4 p{-20, 20, -20, 1};
  for (auto&& light : w->get_light_sources()) {
    ASSERT_FALSE(light::is_shadowed(*w, *light, p));
  }
}

TEST(ShadowTests, PointBetweenLightAndObject) {
  auto w = World::default_world();
  glm::vec4 p{-2, 2, -2, 1};
  for (auto&& light : w->get_light_sources()) {
    ASSERT_FALSE(light::is_shadowed(*w, *light, p));
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}