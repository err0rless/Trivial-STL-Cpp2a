#ifndef _TRIV_STL_VARIANT_H_
#define _TRIV_STL_VARIANT_H_

#include <exception>
#include <iostream>

// References
// - https://github.com/llvm/llvm-project/blob/main/libcxx/include/variant
// - https://en.cppreference.com/w/cpp/utility/variant/variant
#include "concepts.h"

namespace triv {

namespace __detail {

template <typename T, typename... Ts> 
  requires (sizeof...(Ts) > 0)
constexpr bool __contains = (std::is_same_v<T, Ts> || ...);

template <typename T, typename... Ts> 
  requires (__contains<T, Ts...>)
constexpr size_t __num_matches = (std::is_same_v<T, Ts> + ...);

// there's only one match
template <typename T, typename... Ts>
concept __unambiguous_match = (__num_matches<T, Ts...> == 1);

// find the index of first occurrence of `T` in `Ts`
template <typename T, typename... Ts>
  requires (__contains<T, Ts...>)
consteval int __index_of(void) {
  constexpr bool __matches[] = { std::is_same_v<T, Ts>..., };
  for (int i = 0; i < sizeof...(Ts); ++i) {
    if (__matches[i]) {
      return i;
    }
  }
  return -1;
}

// Find unambiguous match for `T` from the parameter pack `Ts` 
template <typename T, typename... Ts>
  requires (__unambiguous_match<T, Ts...>)
constexpr auto __exact_match_idx = __index_of<T, Ts...>();

}

class bad_access_variant : public std::exception {
public:
    bad_access_variant() {}
};

// The concept `VariantType` is satisfied if and only if the types packed in 
// `Ts` are all suitable for variant
template <typename... Ts>
concept VariantType = 
  ((!is_void<Ts> && !is_reference<Ts> && !is_array<Ts>) && ...);

// Check if the index is in range
template <size_t Idx, typename... Params>
concept range_check = (Idx >= 0 && Idx < sizeof...(Params));

enum class __ip_t {} __in_place;

template <size_t Index>
struct __ip_index_t {
  static constexpr auto value = Index;
};

struct __valueless_t {};

// Value container
template <size_t Index, typename T>
struct __variant_alt {
  using value_type = T;
  
  template <typename... Params>
  __variant_alt(Params&&... Args) 
    : __value(std::forward<Params>(Args)...) {}
  
  value_type __value;
};

template <size_t Index, VariantType... Ts>
union __variant_union;

template <size_t Index>
union __variant_union<Index> {};

template <size_t Index, VariantType T, VariantType... Ts>
union __variant_union<Index, T, Ts...> {
public:
  __variant_union(__valueless_t) : __empty() {}

  template <typename... Params>
  __variant_union(__ip_index_t<0>, Params&&... Args) 
    : __alt(std::forward<Params>(Args)...) {}
  
  template <size_t I, typename... Params> requires (I > 0)
  __variant_union(__ip_index_t<I>, Params&&... Args) 
    : __next(__ip_index_t<I - 1>{}, std::forward<Params>(Args)...) {}

  template <size_t I> requires (I >= 0)
  constexpr auto get(void) const {
    if constexpr (I == 0) {
      return __alt.__value;
    } else {
      return __next.template get<I - 1>();
    }
  }
private:
  char __empty;
  __variant_alt<Index, T> __alt;
  __variant_union<Index + 1, Ts...> __next;
};

template <VariantType... Params> requires (sizeof...(Params) > 0)
class __variant_base {
public:
  constexpr __variant_base(__valueless_t) 
    : __data(__valueless_t{}) {}

  template <size_t I, typename... CParams> 
    requires (range_check<I, Params...>)
  constexpr __variant_base(__ip_index_t<I> IpIdx, CParams&&... Args)
    : __data(IpIdx, std::forward<CParams>(Args)...)
    , __index(I) {}
  
  template <size_t Idx>
    requires (range_check<Idx, Params...>)
  constexpr auto get(void) const {
    if (Idx != __index) {
      // The member at Idx is inactive or Idx is out of range
      throw bad_access_variant();
    }
    return __data.template get<Idx>();
  }

  template <typename U> 
    requires (__detail::__unambiguous_match<U, Params...>)
  constexpr auto get(void) const {
    constexpr auto Idx = __detail::__exact_match_idx<U, Params...>;
    return get<Idx>();
  }
private:
  __variant_union<0, Params...> __data;

  // index of the active alternative
  size_t __index;
};

} // namespace triv

// Interface
namespace triv {

template <VariantType... Params> requires (sizeof...(Params) > 0)
class variant : public __variant_base<Params...> {
  using __base_t = __variant_base<Params...>;
public:
  constexpr variant() : __base_t(__valueless_t{}) {};

  // this overload participates in overload resolution only if `T` is in `Params`
  template <typename T, 
            int IpIdx = __detail::__exact_match_idx<T, Params...>>
    requires (IpIdx != -1)
  constexpr variant(T&& Arg) 
    : __base_t(__ip_index_t<IpIdx>{}, std::forward<T>(Arg)) {}

  constexpr variant(const variant&) = default;
  constexpr variant(variant&&) = default;
};

template <size_t I, typename... Ts>
constexpr auto get(const variant<Ts...>& v) {
  return v.template get<I>();
}

template <typename T, typename... Ts>
constexpr auto get(const variant<Ts...>& v) {
  return v.template get<T>();
}

}

#endif