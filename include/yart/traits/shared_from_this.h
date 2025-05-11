#pragma once

#include <memory>
#include <type_traits>

namespace yart {
  namespace traits {

    template <class Base, class Self> struct enable_shared_from_this : public Base {
      template <typename... Args> enable_shared_from_this(Args&&... args)
          : Base(std::forward<Args>(args)...) {}

      std::shared_ptr<Self> shared_from_this() {
        // static_assert(
        //     std::is_base_of_v<std::enable_shared_from_this<Base>, Base>
        //         || std::is_base_of_v<enable_shared_from_this<Base, Self>, Base>,
        //     "Base class has to inherit from yart::traits::enable_shared_from_this or "
        //     "std::enable_shared_from_this");
        return std::static_pointer_cast<Self>(Base::shared_from_this());
      }
    };

  }  // namespace traits

}  // namespace yart
