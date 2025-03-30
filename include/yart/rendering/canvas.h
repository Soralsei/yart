#include <array>
#include <cstdint>

#include "yart/rendering/color.h"
#include "yart/traits/sized.h"

namespace yart {

  namespace rendering {
    template <uint32_t W, uint32_t H> class Canvas : traits::Sized {
    private:
      int width;
      int height;
      std::array<Color, W * H> pixels;

    public:
      Canvas();
      Canvas(const Canvas& other);
      Canvas(Canvas<W, H>&& other) noexcept;

      Canvas<W, H>& operator=(Canvas<W, H>&& other) noexcept;
      Canvas<W, H>& operator=(const Canvas<W, H>& other);

      Color& operator()(int x, int y) const;

      void setPixel(int x, int y, const Color& color);
      Color getPixel(int x, int y) const;

      // Implementing the Sized interface
      uint32_t getWidth() const override;
      uint32_t getHeight() const override;

      Color* getPixels() const;

      ~Canvas() = default;
    };
  }  // namespace rendering

}  // namespace yart
