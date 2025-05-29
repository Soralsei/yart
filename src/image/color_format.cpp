#include "yart/image/color_format.h"

#include "yart/image/color.h"

namespace yart {

  namespace image {
    using namespace color;
    uint32_t RGB888Format::colorToFormat(const Color& color) const {
      uint8_t r = static_cast<uint8_t>(std::min(color.getR() * 255, 255.0f));
      uint8_t g = static_cast<uint8_t>(std::min(color.getG() * 255, 255.0f));
      uint8_t b = static_cast<uint8_t>(std::min(color.getB() * 255, 255.0f));
      return static_cast<uint32_t>((b << 16) | (g << 8) | r);  // Little endian -> RGB not BGR
    }
    Color RGB888Format::formatToColor(const uint32_t& format) const {
      uint8_t b = (format >> 16) & 0xFF;
      uint8_t g = (format >> 8) & 0xFF;
      uint8_t r = format & 0xFF;
      return Color(r / 255.0f, g / 255.0f, b / 255.0f);
    }
    inline int RGB888Format::bitDepth() const {
      return 8;  // 8 bits per channel
    }
    inline int RGB888Format::channelCount() const {
      return 3;  // 3 channels (R, G, B)
    }

    uint32_t RGBA8888Format::colorToFormat(const Color& color) const {
      uint8_t r = static_cast<uint8_t>(std::min(color.getR() * 255, 255.0f));
      uint8_t g = static_cast<uint8_t>(std::min(color.getG() * 255, 255.0f));
      uint8_t b = static_cast<uint8_t>(std::min(color.getB() * 255, 255.0f));
      uint8_t a = static_cast<uint8_t>(std::min(color.getA() * 255, 255.0f));
      return static_cast<uint32_t>((a << 24u) | (b << 16u) | (g << 8u)
                                   | r);  // Little endian -> RGBA not ABGR
    }
    Color RGBA8888Format::formatToColor(const uint32_t& format) const {
      uint8_t a = (format >> 24) & 0xFF;
      uint8_t b = (format >> 16) & 0xFF;
      uint8_t g = (format >> 8) & 0xFF;
      uint8_t r = format & 0xFF;
      return Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
    }
    inline int RGBA8888Format::bitDepth() const {
      return 8;  // 8 bits per channel
    }
    inline int RGBA8888Format::channelCount() const {
      return 4;  // 3 channels (R, G, B)
    }

    uint16_t RGB565Format::colorToFormat(const Color& color) const {
      uint8_t r = static_cast<uint8_t>(std::min(color.getR() * 31, 31.0f));
      uint8_t g = static_cast<uint8_t>(std::min(color.getG() * 63, 63.0f));
      uint8_t b = static_cast<uint8_t>(std::min(color.getB() * 31, 31.0f));
      return static_cast<uint16_t>((b << 11) | (g << 5) | r);
    }
    Color RGB565Format::formatToColor(const uint16_t& format) const {
      uint8_t b = (format >> 11) & 0x1F;
      uint8_t g = (format >> 5) & 0x3F;
      uint8_t r = format & 0x1F;
      return Color(r / 31.0f, g / 63.0f, b / 31.0f);
    }
    inline int RGB565Format::bitDepth() const {
      return 6;  // 5,6,5 bits per channel -> 16 bits total
    }
    inline int RGB565Format::channelCount() const {
      return 3;  // 3 channels (R, G, B)
    }

    uint16_t RGBA4444Format::colorToFormat(const Color& color) const {
      uint8_t r = static_cast<uint8_t>(std::min(color.getR() * 15, 15.0f));
      uint8_t g = static_cast<uint8_t>(std::min(color.getG() * 15, 15.0f));
      uint8_t b = static_cast<uint8_t>(std::min(color.getB() * 15, 15.0f));
      uint8_t a = static_cast<uint8_t>(std::min(color.getA() * 15, 15.0f));
      return static_cast<uint16_t>((r << 12) | (g << 8) | (b << 4) | a);
    }
    Color RGBA4444Format::formatToColor(const uint16_t& format) const {
      uint8_t r = (format >> 12) & 0x0F;
      uint8_t g = (format >> 8) & 0x0F;
      uint8_t b = (format >> 4) & 0x0F;
      uint8_t a = format & 0x0F;
      return Color(r / 15.0f, g / 15.0f, b / 15.0f, a / 15.0f);
    }
    int RGBA4444Format::bitDepth() const {
      return 4;  // 5,6,5 bits per channel -> 16 bits total
    }
    int RGBA4444Format::channelCount() const {
      return 4;  // 3 channels (R, G, B)
    }
  }  // namespace image

}  // namespace yart
