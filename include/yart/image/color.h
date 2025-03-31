#pragma once

#include <cstdint>
#include <ostream>

namespace yart {

  namespace image {
    class Color {
      template<uint32_t W, uint32_t H> friend class Canvas;

    private:
      float r = 0.0f;
      float g = 0.0f;
      float b = 0.0f;
      float a = 1.0f;

    public:
      Color(float r, float g, float b, float a);
      Color(float r, float g, float b);
      Color();

      Color& operator+=(const Color& rhs);
      friend Color operator+(const Color& lhs, const Color& rhs);
      Color& operator-=(const Color& rhs);
      friend Color operator-(const Color& lhs, const Color& rhs);

      Color& operator*=(float rhs);
      friend Color operator*(const Color& lhs, float rhs);

      Color& operator*=(const Color& rhs);
      friend Color operator*(const Color& lhs, const Color& rhs);

      friend bool operator==(const Color& lhs, const Color& rhs);
      friend bool operator!=(const Color& lhs, const Color& rhs);

      friend std::ostream& operator<<(std::ostream& outs, const Color& color);

      inline float getR() const { return r; }
      inline float getG() const { return g; }
      inline float getB() const { return b; }
      inline float getA() const { return a; }
    };

    extern Color BLACK;
    extern Color WHITE;
    extern Color RED;
    extern Color GREEN;
    extern Color BLUE;
    extern Color CYAN;
    extern Color MAGENTA;
    extern Color YELLOW;
  }  // namespace image

}  // namespace yart
