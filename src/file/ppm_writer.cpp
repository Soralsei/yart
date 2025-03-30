#pragma once
#include <iostream>
#include <fstream>
#include <cstdint>

#include "yart/file/image_writer.h"
#include "yart/rendering/color.h"
#include "yart/rendering/color_format.h"
#include "yart/file/ppm_writer.h"
#include "ppm_writer.h"

namespace yart {
  namespace file {
    
    PPMWriter::PPMWriter(PPMFormat format = PPMFormat::P3) : format(format) {}
    bool PPMWriter::write(const char* filename, const rendering::Color* data, int width, int height) {
      std::ofstream file(filename, std::ios::binary);
      if (!file.good())
      {
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
        std::cerr << "Unsupported PPM format" << std::endl;
        return false;
      }
      file.flush();
      bool ret = !file.bad();
      file.close();     

      return ret;
    }

    void PPMWriter::writeHeader(std::ofstream& file, int width, int height) {
      if (format == PPMFormat::P3) {
        file << "P3\n";
      } else if (format == PPMFormat::P6) {
        file << "P6\n";
      }
      file << width << " " << height << "\n255\n";
    }

    void PPMWriter::writeDataP3(std::ofstream& file, const rendering::Color* data, int width, int height) {
      for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
          int index = (y * width + x) * 3;
          uint32_t color = color_format.colorToFormat(data[index]);
          uint8_t r = (color >> 16) & 0xFF;
          uint8_t g = (color >> 8) & 0xFF;
          uint8_t b = color & 0xFF;
          file << std::to_string(r) << " " << std::to_string(g) << " " << std::to_string(b) << "\n";
        }
      }
    }
  }  // namespace file

}  // namespace yart
