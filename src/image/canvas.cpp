#include "yart/image/canvas.h"

#include <algorithm>

namespace yart {

  namespace image {

    Canvas::Canvas(int _width, int _height)
        : width(_width), height(_height), pixels(std::make_unique<Color[]>(_width * _height)) {}

    Canvas::Canvas(const Canvas& other) : Canvas(other.width, other.height) {
      std::copy(other.pixels.get(), other.pixels.get() + width * height, pixels.get());
    }

    Canvas::Canvas(Canvas&& other) noexcept
        : width(other.width), height(other.height), pixels(std::move(other.pixels)) {
      other.width = 0;
      other.height = 0;
    }

    Canvas& Canvas::operator=(Canvas&& other) noexcept {
      if (this != &other) {
        width = other.width;
        height = other.height;
        pixels = std::move(other.pixels);
        other.width = 0;
        other.height = 0;
      }
      return *this;
    }

    Canvas& Canvas::operator=(const Canvas& other) {
      if (this != &other) {
        width = other.width;
        height = other.height;

        pixels.reset();
        pixels = std::make_unique<Color[]>(width * height);

        std::copy(other.pixels.get(), other.pixels.get() + width * height, pixels.get());
      }
      return *this;
    }

    Color Canvas::operator()(int x, int y) const {
      if (x >= width || y >= height || x < 0 || y < 0) {
        throw std::out_of_range("Canvas coordinates out of range");
      }
      return pixels[y * width + x];
    }

    void Canvas::setPixel(int x, int y, const Color& color) {
      if (x >= width || y >= height || x < 0 || y < 0) {
        throw std::out_of_range("Canvas coordinates out of range");
      }
      pixels[y * width + x] = color;
    }

    Color Canvas::getPixel(int x, int y) const { return (*this)(x, y); }

    int Canvas::getWidth() const { return width; }

    int Canvas::getHeight() const { return height; }

    const Color* Canvas::getPixels() const { return pixels.get(); }

    void Canvas::fill(const Color& color) {
      std::fill(pixels.get(), pixels.get() + width * height, color);
    }

  }  // namespace image

}  // namespace yart
