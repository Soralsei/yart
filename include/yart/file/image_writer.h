#pragma once

namespace yart {
  namespace color {
    class Color;
  }
  namespace file {
    class ImageWriter {
    public:
      ImageWriter() = default;
      virtual ~ImageWriter() = default;

      virtual bool write(const char* filename, const color::Color* data, int width, int height) = 0;
    };
  }  // namespace file

}  // namespace yart
