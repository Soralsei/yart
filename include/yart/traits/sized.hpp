#pragma once

#include <cstdint>
namespace yart {
  namespace traits {
    class Sized {
    public:
      virtual ~Sized() {}
      virtual uint32_t getWidth() const = 0;
      virtual uint32_t getHeight() const = 0;
    };
  }  // namespace traits

}  // namespace yart