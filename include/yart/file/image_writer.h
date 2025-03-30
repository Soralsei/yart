#pragma once
#include <cstdint>
#include "yart/rendering/color_format.h"

namespace yart {
  namespace file {
    class ImageWriter {
    public:
      ImageWriter() = default;
      virtual ~ImageWriter() = default;

      virtual bool write(const char* filename, const rendering::Color* data, int width, int height) = 0;
    };
  }  // namespace file

}  // namespace yart
