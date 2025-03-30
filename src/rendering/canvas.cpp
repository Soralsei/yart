#include "yart/rendering/canvas.h"
#include "yart/rendering/color.h"

namespace yart {
  namespace rendering {

    template <uint32_t W, uint32_t H> Canvas<W, H>::Canvas() : width(W), height(H) {
      for (int i = 0; i < W * H; ++i) {
        pixels[i] = BLACK;
      }
    }

    template <uint32_t W, uint32_t H> Canvas<W, H>::Canvas(const Canvas<W, H>& other)
        : width(other.width), height(other.height), pixels(other.pixels) {}

    template <uint32_t W, uint32_t H>
    Canvas<W, H>& Canvas<W, H>::operator=(const Canvas<W, H>& other) {
      if (this != &other) {
        width = other.width;
        height = other.height;
        pixels = other.pixels;
      }
      return *this;
    }

    template <uint32_t W, uint32_t H> Canvas<W, H>::Canvas(Canvas<W, H>&& other) noexcept
        : width(other.width), height(other.height), pixels(std::move(other.pixels)) {
      other.width = 0;
      other.height = 0;
    }

    template <uint32_t W, uint32_t H>
    Canvas<W, H>& Canvas<W, H>::operator=(Canvas<W, H>&& other) noexcept {
      if (this != &other) {
        width = other.width;
        height = other.height;
        pixels = std::move(other.pixels);
        other.width = 0;
        other.height = 0;
      }
      return *this;
    }

    template <uint32_t W, uint32_t H> Color& Canvas<W, H>::operator()(int x, int y) const {
      if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Canvas coordinates out of range");
      }
      return pixels[y * width + x];
    }

    template <uint32_t W, uint32_t H>
    void Canvas<W, H>::setPixel(int x, int y, const Color& color) {
      if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Canvas coordinates out of range");
      }
      pixels[y * width + x] = color;
    }

    template <uint32_t W, uint32_t H> Color Canvas<W, H>::getPixel(int x, int y) const {
      return this(x, y);
    }

    template <uint32_t W, uint32_t H> Color* Canvas<W, H>::getPixels() const {
      return pixels.data();
    }

    template <uint32_t W, uint32_t H> uint32_t Canvas<W, H>::getWidth() const { return width; }
    template <uint32_t W, uint32_t H> uint32_t Canvas<W, H>::getHeight() const { return height; }

  }  // namespace rendering

}  // namespace yart
