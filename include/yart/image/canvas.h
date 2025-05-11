#pragma once
#include <cstdint>
#include <memory>

#include "yart/image/color.h"
#include "yart/traits/sized.h"

namespace yart {

  namespace image {
    using namespace color;
    class Canvas : public traits::Sized {
    private:
      uint32_t width;
      uint32_t height;
      std::unique_ptr<Color[]> pixels;

    public:
      Canvas(uint32_t width, uint32_t height);
      Canvas(const Canvas& other);
      Canvas(Canvas&& other) noexcept;
      ~Canvas() = default;

      Canvas& operator=(Canvas&& other) noexcept;
      Canvas& operator=(const Canvas& other);

      Color operator()(uint32_t x, uint32_t y) const;
      void setPixel(uint32_t x, uint32_t y, const Color& color);
      Color getPixel(uint32_t x, uint32_t y) const;

      // Implementing the Sized interface
      uint32_t getWidth() const override;
      uint32_t getHeight() const override;

      const Color* getPixels() const;
      void fill(const Color& color);
    };
  }  // namespace image

}  // namespace yart
