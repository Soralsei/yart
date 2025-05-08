#pragma once
#include <cstdint>

#include "yart/image/color.h"

namespace yart {

  namespace image {

    template <typename T> class ColorFormat {
    public:
      ColorFormat() = default;
      virtual ~ColorFormat() = default;
      virtual T colorToFormat(const color::Color& color) = 0;
      virtual color::Color formatToColor(const T& format) = 0;
    };

    class RGB888Format : public ColorFormat<uint32_t>  // Assuming RGB888 is represented as uint32_t
    {
    public:
      uint32_t colorToFormat(const color::Color& color) override;
      color::Color formatToColor(const uint32_t& format) override;
    };

    class RGBA8888Format
        : public ColorFormat<uint32_t>  // Assuming RGBA8888 is represented as uint32_t
    {
    public:
      uint32_t colorToFormat(const color::Color& color) override;
      color::Color formatToColor(const uint32_t& format) override;
    };

    class RGB565Format : public ColorFormat<uint16_t>  // Assuming RGB565 is represented as uint16_t
    {
    public:
      uint16_t colorToFormat(const color::Color& color) override;
      color::Color formatToColor(const uint16_t& format) override;
    };

    class RGBA4444Format
        : public ColorFormat<uint16_t>  // Assuming RGBA4444 is represented as uint16_t
    {
    public:
      uint16_t colorToFormat(const color::Color& color) override;
      color::Color formatToColor(const uint16_t& format) override;
    };

  }  // namespace image

}  // namespace yart
