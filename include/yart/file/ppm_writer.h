#pragma once

#include "yart/file/image_writer.h"
#include "yart/image/color.h"
#include "yart/image/color_format.h"

#ifdef __unix__ /* __unix__ is usually defined by compilers targeting Unix systems */
#  define NEWLINE '\n'
#elif defined(_WIN32) || defined(WIN32) /* _Win32 is usually defined by compilers targeting 32 or \
                                           64 bit Windows systems */
#  define NEWLINE '\r\n'
#endif

namespace yart {
  namespace file {
    class PPMWriter : public ImageWriter {
    public:
      enum class PPMFormat { P3, P6 };

    private:
      PPMFormat format;
      image::RGB888Format color_format;

    public:
      PPMWriter(PPMFormat format = PPMFormat::P3);
      ~PPMWriter() override = default;
      bool write(const char* filename, const color::Color* data, int width, int height) override;

    private:
      void writeHeader(std::ofstream& file, int width, int height);
      void writeDataP3(std::ofstream& file, const color::Color* data, int width, int height);
      void writeDataP6(std::ofstream& file, const color::Color* data, int width, int height);
    };

  }  // namespace file

}  // namespace yart
