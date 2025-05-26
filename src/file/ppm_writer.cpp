#include "yart/file/ppm_writer.h"

#include <cstdint>
#include <fstream>
#include <iostream>

#include "yart/file/image_writer.h"
#include "yart/image/color.h"
#include "yart/image/color_format.h"

namespace yart {
  namespace file {

    PPMWriter::PPMWriter(PPMFormat _format) : format(_format) {}
    bool PPMWriter::write(const char* filename, const color::Color* data, int width, int height) {
      std::ofstream file(filename, std::ios::binary);
      if (!file.good()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return false;
      }

      // Write the header
      writeHeader(file, width, height);
      // Write the pixel data
      if (format == PPMFormat::P3) {
        writeDataP3(file, data, width, height);
      } else if (format == PPMFormat::P6) {
        writeDataP6(file, data, width, height);
      } else {
        std::cerr << "Unsupported PPM format" << NEWLINE;
        return false;
      }
      file << std::endl;
      bool ret = !file.bad();
      file.close();

      return ret;
    }

    void PPMWriter::writeHeader(std::ofstream& file, int width, int height) {
      char separator;
      if (format == PPMFormat::P3) {
        file << "P3";
        separator = NEWLINE;
      } else if (format == PPMFormat::P6) {
        file << "P6";
        separator = '\n';
      }
      file << separator << width << ' ' << height << separator << "255" << separator;
    }

    void PPMWriter::writeDataP3(std::ofstream& file, const color::Color* data, int width,
                                int height) {
      for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
          int index = y * width + x;
          uint32_t color = color_format.colorToFormat(data[index]);
          uint8_t r = (color >> 16) & 0xFF;
          uint8_t g = (color >> 8) & 0xFF;
          uint8_t b = color & 0xFF;
          file << std::to_string(r) << " " << std::to_string(g) << " " << std::to_string(b);
          if (index % 70 == 0 && index != 0) {
            file << "\n";
          } else {
            file << " ";
          }
        }
      }
    }

    void PPMWriter::writeDataP6(std::ofstream& file, const color::Color* data, int width,
                                int height) {
      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          int index = y * width + x;
          uint32_t color = color_format.colorToFormat(data[index]);
          uint8_t r = (color >> 16) & 0xFF;
          uint8_t g = (color >> 8) & 0xFF;
          uint8_t b = color & 0xFF;
          file << r << g << b;
        }
        file << "\n";
      }
    }
  }  // namespace file

}  // namespace yart
