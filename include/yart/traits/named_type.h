#pragma once
#define DECLARE_TYPE_NAME(Type) template <> const char* type_name<Type>::name = #Type;
#define VAR_TYPE_NAME(var) (type_name<decltype(var)>::name)
#define TYPE_NAME(Type) (type_name<Type>::name)

namespace yart {
  namespace traits {

    template <typename T> struct type_name {
      static const char* name;
    };
  }  // namespace traits

}  // namespace yart
