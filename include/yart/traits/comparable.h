#pragma once
#include <type_traits>
#include <utility>

namespace yart {

  namespace traits {

    template <typename T> struct comparable_base {
      virtual ~comparable_base() {}
      virtual bool is_equal(const T& b) const = 0;
      virtual bool self_equal(const T& other) const = 0;
    };

    template <typename ActualType, typename Ancestor, typename Parent = Ancestor> class comparable
        : public Parent {
      static_assert(std::is_base_of_v<comparable_base<Ancestor>, Ancestor>);

    public:
      template <typename... Args> comparable(Args&&... args)
          : Parent(std::forward<Args>(args)...) {}

    protected:
      virtual bool is_equal(const Ancestor& b) const override {
        const auto& other = static_cast<const ActualType&>(b);
        return Parent::is_equal(other) && self_equal(other);
      }
      virtual bool self_equal(const ActualType& other) const = 0;
      using Parent::self_equal;
    };

  }  // namespace traits

}  // namespace yart
