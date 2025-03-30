#include "yart/rendering/color_format.h"

#include "yart/rendering/color.h"

namespace yart {

  namespace rendering {
    uint32_t RGB888Format::colorToFormat(const Color& color) {
      uint8_t r = static_cast<uint8_t>(color.getR() * 255);
      uint8_t g = static_cast<uint8_t>(color.getG() * 255);
      uint8_t b = static_cast<uint8_t>(color.getB() * 255);
      return (r << 16) | (g << 8) | b;
    }
    Color RGB888Format::formatToColor(const uint32_t& format) {
      uint8_t r = (format >> 16) & 0xFF;
      uint8_t g = (format >> 8) & 0xFF;
      uint8_t b = format & 0xFF;
      return Color(r / 255.0f, g / 255.0f, b / 255.0f);
    }
    uint32_t RGBA8888Format::colorToFormat(const Color& color) {
      uint8_t r = static_cast<uint8_t>(color.getR() * 255);
      uint8_t g = static_cast<uint8_t>(color.getG() * 255);
      uint8_t b = static_cast<uint8_t>(color.getB() * 255);
      uint8_t a = static_cast<uint8_t>(color.getA() * 255);
      return (r << 24) | (g << 16) | (b << 8) | a;
    }
    Color RGBA8888Format::formatToColor(const uint32_t& format) {
      uint8_t r = (format >> 24) & 0xFF;
      uint8_t g = (format >> 16) & 0xFF;
      uint8_t b = (format >> 8) & 0xFF;
      uint8_t a = format & 0xFF;
      return Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
    }
    uint16_t RGB565Format::colorToFormat(const Color& color) {
      uint8_t r = static_cast<uint8_t>(color.getR() * 31);
      uint8_t g = static_cast<uint8_t>(color.getG() * 63);
      uint8_t b = static_cast<uint8_t>(color.getB() * 31);
      return (r << 11) | (g << 5) | b;
    }
    Color RGB565Format::formatToColor(const uint16_t& format) {
      uint8_t r = (format >> 11) & 0x1F;
      uint8_t g = (format >> 5) & 0x3F;
      uint8_t b = format & 0x1F;
      return Color(r / 31.0f, g / 63.0f, b / 31.0f);
    }
    uint16_t RGBA4444Format::colorToFormat(const Color& color) {
      uint8_t r = static_cast<uint8_t>(color.getR() * 15);
      uint8_t g = static_cast<uint8_t>(color.getG() * 15);
      uint8_t b = static_cast<uint8_t>(color.getB() * 15);
      uint8_t a = static_cast<uint8_t>(color.getA() * 15);
      return (r << 12) | (g << 8) | (b << 4) | a;
    }
    Color RGBA4444Format::formatToColor(const uint16_t& format) {
      uint8_t r = (format >> 12) & 0x0F;
      uint8_t g = (format >> 8) & 0x0F;
      uint8_t b = (format >> 4) & 0x0F;
      uint8_t a = format & 0x0F;
      return Color(r / 15.0f, g / 15.0f, b / 15.0f, a / 15.0f);
    }
  }  // namespace rendering

}  // namespace yart
