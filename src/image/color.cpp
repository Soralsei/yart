#include "yart/image/color.h"

#include <algorithm>

#include "yart/math/math.h"

namespace yart  // namespace color
{
  namespace image {
    Color BLACK(0, 0, 0);
    Color WHITE(1, 1, 1);
    Color RED(1, 0, 0);
    Color GREEN(0, 1, 0);
    Color BLUE(0, 0, 1);
    Color YELLOW(1, 1, 0);
    Color CYAN(0, 1, 1);
    Color MAGENTA(1, 0, 1);

    Color::Color(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) {
      a = std::clamp(a, 0.0f, 1.0f);
    }
    Color::Color(float _r, float _g, float _b) : r(_r), g(_g), b(_b), a(1.0f) {}

    Color::Color() : r(0), g(0), b(0), a(1) {}

    bool operator==(const Color& lhs, const Color& rhs) {
      return (math::approx_equals(lhs.r, rhs.r) && math::approx_equals(lhs.g, rhs.g)
              && math::approx_equals(lhs.b, rhs.b) && math::approx_equals(lhs.a, rhs.a));
    }
    bool operator!=(const Color& lhs, const Color& rhs) { return !(lhs == rhs); }

    Color& Color::operator+=(const Color& rhs) {
      r += rhs.r;
      g += rhs.g;
      b += rhs.b;
      return *this;
    }
    Color operator+(const Color& lhs, const Color& rhs) {
      return Color(lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b);
    }
    Color& Color::operator-=(const Color& rhs) {
      r -= rhs.r;
      g -= rhs.g;
      b -= rhs.b;
      return *this;
    }
    Color operator-(const Color& lhs, const Color& rhs) {
      return Color(lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b);
    }
    Color& Color::operator*=(const Color& rhs) {
      r *= rhs.r;
      g *= rhs.g;
      b *= rhs.b;
      return *this;
    }
    Color operator*(const Color& lhs, const Color& rhs) {
      return Color(lhs.r * rhs.r, lhs.g * rhs.g, lhs.b * rhs.b);
    }
    Color& Color::operator*=(float rhs) {
      r *= rhs;
      g *= rhs;
      b *= rhs;
      return *this;
    }
    Color operator*(const Color& lhs, float rhs) {
      return Color(lhs.r * rhs, lhs.g * rhs, lhs.b * rhs);
    }

    std::ostream& operator<<(std::ostream& outs, const Color& color) {
      outs << "Color(" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")";
      return outs;
    }
  }  // namespace color

}  // namespace yart
