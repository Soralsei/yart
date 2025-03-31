#include <gtest/gtest.h>

#include <fstream>
#include <string>

#include "yart/file/ppm_writer.h"
#include "yart/image/canvas.h"
#include "yart/image/color.h"

using namespace yart;

TEST(PPMTest, HeaderP3) {
  auto filename = "/home/sora/testp3.ppm";
  image::Canvas<5, 3> canvas{};
  file::PPMWriter writer;

  bool success = writer.write(filename, canvas.getPixels(), canvas.getWidth(),
                              canvas.getHeight());
  ASSERT_TRUE(success);

  std::ifstream file(filename, std::ios::binary);
  std::string header;
  for (uint32_t i = 0; i < 3; i++) {
    std::string current;
    std::getline(file, current);
    if (file.good()) {
      current += '\n';
    }
    header += current;
  }
  std::cout << header;
  std::string expected = "P3\n5 3\n255\n";

  ASSERT_EQ(header, expected);

  EXPECT_TRUE(true);
}

TEST(PPMTest, HeaderP6) {
  auto filename = "/home/sora/testp6.ppm";
  image::Canvas<5, 3> canvas{};
  file::PPMWriter writer{file::PPMWriter::PPMFormat::P6};

  bool success = writer.write(filename, canvas.getPixels(), canvas.getWidth(),
                              canvas.getHeight());
  ASSERT_TRUE(success);

  std::ifstream file(filename, std::ios::binary);
  std::string header;
  for (uint32_t i = 0; i < 3; i++) {
    std::string current;
    std::getline(file, current);
    if (file.good()) {
      current += '\n';
    }
    header += current;
  }
  std::cout << header;
  std::string expected = "P6\n5 3\n255\n";

  ASSERT_EQ(header, expected);

  EXPECT_TRUE(true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
