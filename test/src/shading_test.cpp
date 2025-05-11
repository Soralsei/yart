#include <gtest/gtest.h>

#include "yart/core/material.h"
#include "yart/geometry/sphere.h"
#include "yart/light/light.h"
#include "yart/light/point_light.h"

class ShadingTest : public testing::Test {
protected:
  ShadingTest() { position = Eigen::Vector3f{0, 0, 0}; }

  yart::Material material;
  Eigen::Vector3f position;
};

TEST(MaterialTest, DefaultConstructor) {
  yart::Material material;
  EXPECT_FLOAT_EQ(material.get_ambient(), 0.1f);
  EXPECT_FLOAT_EQ(material.get_diffuse(), 0.9f);
  EXPECT_FLOAT_EQ(material.get_specular(), 0.9f);
  EXPECT_FLOAT_EQ(material.get_shininess(), 200.0f);
}

TEST(MaterialTest, ShapeHasDefaultMaterial) {
  yart::geometry::Sphere sphere;
  EXPECT_FLOAT_EQ(sphere.get_material().get_ambient(), 0.1f);
  EXPECT_FLOAT_EQ(sphere.get_material().get_diffuse(), 0.9f);
  EXPECT_FLOAT_EQ(sphere.get_material().get_specular(), 0.9f);
  EXPECT_FLOAT_EQ(sphere.get_material().get_shininess(), 200.0f);
}

TEST(MaterialTest, MaterialAssign) {
  yart::geometry::Sphere sphere;

  EXPECT_FLOAT_EQ(sphere.get_material().get_ambient(), 0.1f);
  EXPECT_FLOAT_EQ(sphere.get_material().get_diffuse(), 0.9f);
  EXPECT_FLOAT_EQ(sphere.get_material().get_specular(), 0.9f);
  EXPECT_FLOAT_EQ(sphere.get_material().get_shininess(), 200.0f);

  yart::Material material;
  material.set_ambient(1);
  sphere.get_material() = material;

  EXPECT_FLOAT_EQ(sphere.get_material().get_ambient(), 1.0f);
  EXPECT_FLOAT_EQ(sphere.get_material().get_diffuse(), 0.9f);
  EXPECT_FLOAT_EQ(sphere.get_material().get_specular(), 0.9f);
  EXPECT_FLOAT_EQ(sphere.get_material().get_shininess(), 200.0f);
}

TEST_F(ShadingTest, EyeBetweenLightAndSurface) {
  auto eye = Eigen::Vector3f{0, 0, -1};
  auto normal = Eigen::Vector3f{0, 0, -1};
  yart::light::PointLight light{Eigen::Vector3f{0, 0, -10}};

  auto result = yart::light::phong_lighting(material, light, position, eye, normal);
  ASSERT_EQ(result, (yart::color::Color{1.9f, 1.9f, 1.9f}));
}

TEST_F(ShadingTest, EyeOffset45Degrees) {
  auto eye = Eigen::Vector3f{0, std::sqrt(2)/2, -std::sqrt(2) / 2};
  auto normal = Eigen::Vector3f{0, 0, -1};
  yart::light::PointLight light{Eigen::Vector3f{0, 0, -10}};

  auto result = yart::light::phong_lighting(material, light, position, eye, normal);
  ASSERT_EQ(result, (yart::color::Color{1.0f, 1.0f, 1.0f}));
}

TEST_F(ShadingTest, LightOffset45Degrees) {
  auto eye = Eigen::Vector3f{0, 0, -1};
  auto normal = Eigen::Vector3f{0, 0, -1};
  yart::light::PointLight light{Eigen::Vector3f{0, 10, -10}};

  auto result = yart::light::phong_lighting(material, light, position, eye, normal);
  ASSERT_EQ(result, (yart::color::Color{0.7364f, 0.7364f, 0.7364f}));
}

TEST_F(ShadingTest, LightAndEyeOffset45Degrees) {
  auto eye = Eigen::Vector3f{0, -std::sqrt(2)/2, -std::sqrt(2) / 2};
  auto normal = Eigen::Vector3f{0, 0, -1};
  yart::light::PointLight light{Eigen::Vector3f{0, 10, -10}};

  auto result = yart::light::phong_lighting(material, light, position, eye, normal);
  ASSERT_EQ(result, (yart::color::Color{1.6364, 1.6364, 1.6364}));
}
TEST_F(ShadingTest, LightBehindSurface) {
  auto eye = Eigen::Vector3f{0, 0, -1};
  auto normal = Eigen::Vector3f{0, 0, -1};
  yart::light::PointLight light{Eigen::Vector3f{0, 0, 10}};

  auto result = yart::light::phong_lighting(material, light, position, eye, normal);
  ASSERT_EQ(result, (yart::color::Color{0.1, 0.1, 0.1}));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}