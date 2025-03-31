#pragma once
#include <array>
#include <cstdint>

#include "yart/rendering/color.h"
#include "yart/traits/sized.h"

namespace yart {

  namespace rendering {
    template <uint32_t W, uint32_t H> class Canvas : traits::Sized {
    private:
      int width = W;
      int height = H;
      std::array<Color, W * H> pixels;

    public:
      Canvas() {
        pixels.fill(BLACK);
      }
      Canvas(const Canvas& other)
          : width(other.width), height(other.height), pixels(other.pixels) {};
      Canvas(Canvas&& other) noexcept
          : width(other.width), height(other.height), pixels(std::move(other.pixels)) {
        other.width = 0;
        other.height = 0;
      }
      ~Canvas() = default;

      Canvas& operator=(Canvas&& other) noexcept {
        if (this != &other) {
          width = other.width;
          height = other.height;
          pixels = std::move(other.pixels);
          other.width = 0;
          other.height = 0;
        }
        return *this;
      }

      Canvas& operator=(const Canvas& other) {
        if (this != &other) {
          width = other.width;
          height = other.height;
          pixels = other.pixels;
        }
        return *this;
      };

      Color operator()(int x, int y) const{
        if (x < 0 || x >= width || y < 0 || y >= height) {
          throw std::out_of_range("Canvas coordinates out of range");
        }
        return pixels[y * width + x];
      }

      void setPixel(int x, int y, const Color& color) {
        if (x < 0 || x >= width || y < 0 || y >= height) {
          throw std::out_of_range("Canvas coordinates out of range");
        }
        pixels[y * width + x] = color;
      }
      Color getPixel(int x, int y) const { return (*this)(x, y); }

      // Implementing the Sized interface
      uint32_t getWidth() const override { return width; }
      uint32_t getHeight() const override { return height; }

      Color* getPixels() const { return pixels.data(); }
    };
  }  // namespace rendering

}  // namespace yart
