#pragma once
#include <memory>

#include "yart/image/color.hpp"
#include "yart/traits/sized.hpp"

namespace yart {

  namespace image {
    using namespace color;
    class Canvas : public traits::Sized {
    private:
      int width;
      int height;
      std::unique_ptr<Color[]> pixels;

    public:
      Canvas(int width, int height);
      Canvas(const Canvas& other);
      Canvas(Canvas&& other) noexcept;
      ~Canvas() = default;

      Canvas& operator=(Canvas&& other) noexcept;
      Canvas& operator=(const Canvas& other);

      Color operator()(int x, int y) const;
      void setPixel(int x, int y, const Color& color);
      Color getPixel(int x, int y) const;

      // Implementing the Sized interface
      int getWidth() const override;
      int getHeight() const override;

      const Color* getPixels() const;
      void fill(const Color& color);
    };
  }  // namespace image

}  // namespace yart
