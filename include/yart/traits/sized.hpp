#pragma once

namespace yart {
  namespace traits {
    class Sized {
    public:
      virtual ~Sized() {}
      virtual int getWidth() const = 0;
      virtual int getHeight() const = 0;
    };
  }  // namespace traits

}  // namespace yart