#include "yart/image/color.h"
#include "yart/image/canvas.h"

#include <gtest/gtest.h>

using namespace yart;

TEST(CanvasTest, Initialization) {
  image::Canvas<10, 20> canvas{};
  ASSERT_EQ(canvas.getWidth(), 10);
  ASSERT_EQ(canvas.getHeight(), 20);

  bool is_all_black = true;
  for (int y = 0; y < canvas.getHeight(); y++)
  {
    for (int x = 0; x < canvas.getWidth(); x++)
    {
      if (canvas(x, y) != color::Black)
      {
        is_all_black = false;
        break;
      }
    }
  }
  ASSERT_EQ(is_all_black, true);
  EXPECT_TRUE(true);
}
TEST(CanvasTest, SetGetPixel) {
  image::Canvas<10, 20> canvas{};
  color::Color color(0.5f, 0.5f, 0.5f);
  canvas.setPixel(5, 10, color);
  color::Color result = canvas.getPixel(5, 10);
  ASSERT_EQ(result, color);
  EXPECT_TRUE(true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
