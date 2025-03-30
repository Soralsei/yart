#pragma once
#include <cstdint>

#include "yart/file/image_writer.h"
#include "yart/rendering/color.h"
#include "yart/rendering/color_format.h"

namespace yart {
  namespace file {
    class PPMWriter : public ImageWriter {
    public:
      enum class PPMFormat { P3, P6 };

    private:
      PPMFormat format;
      rendering::RGB888Format color_format;

    public:
      PPMWriter(PPMFormat format = PPMFormat::P3) : format(format) {}
      ~PPMWriter() override = default;
      // bool write(const char* filename, const uint8_t* data, int width, int height) override;
      bool write(const char* filename, const rendering::Color* data, int width, int height) override;

    private:
      void writeHeader(std::ofstream& file, int width, int height);
      void writeDataP3(std::ofstream& file, const rendering::Color* data, int width, int height);
      void writeDataP6(std::ofstream& file, const rendering::Color* data, int width, int height);
    };

  }  // namespace file

}  // namespace yart
