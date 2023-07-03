#ifndef _TRIV_CONCEPTS_H_
#define _TRIV_CONCEPTS_H_

#include <type_traits>

namespace triv {
inline namespace concepts {

// same_as
template <typename T, typename U>
concept same_as = std::is_same_v<T, U> && std::is_same_v<U, T>;

template <typename T, typename U>
concept is_same = std::is_same_v<T, U> && std::is_same_v<U, T>;

// default_constructible
template <typename T>
concept default_constructible = 
  std::is_default_constructible_v<T> &&
  requires { T{}; };

template <typename T>
concept is_reference = std::is_reference_v<T>;

template <typename T>
concept is_void = std::is_void_v<T>;

template <typename T>
concept is_array = std::is_array_v<T>;

template <typename T, typename U>
concept convertible_to = 
  std::is_convertible_v<T, U> &&
  requires { static_cast<U>(std::declval<T>()); };

}
}

#endif // _TRIV_CONCEPTS_H_
