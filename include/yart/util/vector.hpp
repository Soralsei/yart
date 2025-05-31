#pragma once
#include <type_traits>
#include <vector>

namespace yart {

  template <typename... Args, typename T = std::common_type_t<Args...>>
  std::vector<T> make_vec(Args&&... args) {
    return std::vector<T>{std::forward<Args>(args)...};
  }

}  // namespace yart
